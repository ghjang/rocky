#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>
#include <type_traits>
#include <functional>
#include <tuple>


template <typename T>
struct context
{
    T & args_;
};


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


template <typename Derived>
struct functor
{
private:
    template <typename Lhs, typename Rhs, typename Context>
    decltype(auto) call_impl(Lhs & lhs, Rhs & rhs, Context & c)
    {
        return Derived::apply(lhs(c), rhs(c));
    }

    template <typename T>
    auto wrap(T & t, std::false_type)
    {
        return std::ref(t);
    }

    template <typename T>
    auto wrap(T && t, std::true_type)
    {
        static_assert(std::is_rvalue_reference<decltype(t)>::value);
        return t;
    }

public:
    auto derived()
    {
        return static_cast<Derived *>(this);
    }

    template <typename T>
    decltype(auto) operator () (context<T> & c)
    {
        return call_impl(derived()->left(), derived()->right(), c);
    }

    template <typename... Args>
    decltype(auto) operator () (Args &&... args)
    {
        auto t = std::make_tuple(
                        wrap(
                            std::forward<Args>(args),
                            std::is_rvalue_reference<decltype(args)>()
                        )...
                 );
        context<decltype(t)> c{ t };
        return (*this)(c);
    }
};


template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct storage;

template <typename Left, typename Right>
struct storage<Left, Right, false, false>
{
    Left & left_;
    Right & right_;
};

template <typename Left, typename Right>
struct storage<Left, Right, false, true>
{
    Left & left_;
    Right right_;
};

template <typename Left, typename Right>
struct storage<Left, Right, true, false>
{
    Left left_;
    Right & right_;
};

template <typename Left, typename Right>
struct storage<Left, Right, true, true>
{
    Left left_;
    Right right_;
};


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

    template <typename T>
    static decltype(auto) apply(T && t, null_terminal)
    {
        return OpTag::apply(std::forward<T>(t), null_terminal{});
    }
};


//==============================================================================
template <typename T>
struct is_callable_node : std::false_type
{ };

template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct is_callable_node<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        : std::true_type
{ };

template <typename T>
struct is_callable_node<terminal<T>>
        : std::true_type
{ };

template <std::size_t i>
struct is_callable_node<place_holder<i>>
        : std::true_type
{ };

template <bool IsValRValRef, typename T>
struct is_callable_node<value_holder<IsValRValRef, T>>
        : std::true_type
{ };


template <typename T>
struct is_expression : std::false_type
{ };

template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct is_expression<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        : std::true_type
{ };


template <typename T>
struct is_terminal : std::is_base_of<terminal<T>, T>
{ };

template <typename T>
struct is_terminal<terminal<T>> : std::true_type
{ };


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
#include "BinaryOperator.h"
#include "UnaryOperator.h"


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
