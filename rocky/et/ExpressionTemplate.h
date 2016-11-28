#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>
#include <type_traits>
#include <functional>
#include <tuple>

#include "rocky/et/OperationPolicy.h"
#include "rocky/et/StoragePolicy.h"
#include "rocky/et/ExpressionTraits.h"


//==============================================================================
template <typename Derived>
struct terminal
{
    auto derived()
    {
        return static_cast<Derived *>(this);
    }

    template <typename Context>
    decltype(auto) operator () (Context & c)
    {
        return (*derived())(c);
    }
};


template <std::size_t i>
struct place_holder
        : terminal<place_holder<i>>
        , std::integral_constant<std::size_t, i>
{
    template <typename Context>
    decltype(auto) operator () (Context & c)
    {
        return std::get<i - 1>(c.args_);
    }
};


template <bool IsValRValRef, typename T>
struct value_holder;

template <typename T>
struct value_holder<false, T>
        : terminal<value_holder<false, T>>
{
    value_holder(T & t)
        : value_(t)
    { }

    template <typename Context>
    T & operator () (Context)
    {
        return value_;
    }

    T & get()
    {
        return value_;
    } 

    T & value_;
};

template <typename T>
struct value_holder<false, T *>
        : terminal<value_holder<false, T *>>
{
    value_holder(T * t)
        : value_(t)
    { }

    template <typename Context>
    T * operator () (Context)
    {
        return value_;
    }

    T * get()
    {
        return value_;
    }

    T * value_;
};

template <typename T>
struct value_holder<true, T>
        : terminal<value_holder<true, T>>
{
    value_holder(T && t)
        : value_(std::move(t))
    { }

    template <typename Context>
    T & operator () (Context)
    {
        return value_;
    }

    T & get()
    {
        return value_;
    }

    T value_;
};


struct null_terminal : terminal<null_terminal>
{
    template <typename Context>
    null_terminal operator () (Context)
    {
        return null_terminal{};
    }
};


//==============================================================================
template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct expression
        : functor<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        , private storage<Left, Right, IsLeftRValRef, IsRightRValRef>
{
    using expression_type = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using storage_base_type = storage<Left, Right, IsLeftRValRef, IsRightRValRef>;

    template <typename L, typename R>
    explicit expression(L && l, R && r)
        : storage_base_type{ std::forward<L>(l), std::forward<R>(r) }
    { }

    auto & left()
    {
        storage_base_type & s = *this;
        return s.left_;
    }

    auto & right()
    {
        storage_base_type & s = *this;
        return s.right_;
    }

    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return OpTag::apply(std::forward<L>(l), std::forward<R>(r));
    }
};


//==============================================================================
#define CREATE_PLACEHOLDER_FILLER_0(...)  \
            ((__VA_ARGS__)) CREATE_PLACEHOLDER_FILLER_1
#define CREATE_PLACEHOLDER_FILLER_1(...)  \
            ((__VA_ARGS__)) CREATE_PLACEHOLDER_FILLER_0
#define CREATE_PLACEHOLDER_FILLER_0_END
#define CREATE_PLACEHOLDER_FILLER_1_END

#define TO_STR_IMPL(s) #s
#define TO_STR(s) TO_STR_IMPL(s)

// refer to http://en.cppreference.com/w/cpp/language/operator_precedence
#include "rocky/et/BinaryOperator.h"
#include "rocky/et/UnaryOperator.h"


//==============================================================================
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef PLACE_HOLDER_MAX_SIZE
#   define PLACE_HOLDER_MAX_SIZE 8
#endif // PLACE_HOLDER_MAX_SIZE

#define ET_place_holder(z, n, unused) static place_holder<n> BOOST_PP_CAT(_, n){};

#define BOOST_PP_LOCAL_MACRO(n)     ET_place_holder(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS       (1, PLACE_HOLDER_MAX_SIZE)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO
#undef ET_place_holder


#endif // ROCKY_ET_H
