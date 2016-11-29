#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>
#include <type_traits>
#include <functional>
#include <tuple>

#include "rocky/et/OperationPolicy.h"
#include "rocky/et/StoragePolicy.h"


//==============================================================================
template <typename Derived>
struct terminal
{
    auto derived()
    { return static_cast<Derived *>(this); }

    template <typename Context>
    decltype(auto) operator () (Context & c)
    { return (*derived())(c); }
};


template <std::size_t i>
struct place_holder
        : terminal<place_holder<i>>
        , std::integral_constant<std::size_t, i>
{
    template <typename Context>
    decltype(auto) operator () (Context & c)
    { return std::get<i - 1>(c.args_); }
};


template <bool IsValRValRef, typename T>
struct value_holder;

template <typename T>
struct value_holder<false, T>
        : terminal<value_holder<false, T>>
{
    value_holder(T & t) : value_(t)
    { }

    template <typename Context>
    T & operator () (Context)
    { return value_; }

    T & get()
    { return value_; } 

    T & value_;
};

template <typename T>
struct value_holder<false, T *>
        : terminal<value_holder<false, T *>>
{
    value_holder(T * t) : value_(t)
    { }

    template <typename Context>
    T * operator () (Context)
    { return value_; }

    T * get()
    { return value_; }

    T * value_;
};

template <typename T>
struct value_holder<true, T>
        : terminal<value_holder<true, T>>
{
    value_holder(T && t) : value_(std::move(t))
    { }

    template <typename Context>
    T & operator () (Context)
    { return value_; }

    T & get()
    { return value_; }

    T value_;
};


struct null_terminal : terminal<null_terminal>
{
    template <typename Context>
    null_terminal operator () (Context)
    { return null_terminal{}; }
};


//==============================================================================
#ifndef ET_STORAGE_TYPE
#   define ET_STORAGE_TYPE default_storage
#endif // ET_STORAGE_TYPE

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    template <typename, typename, bool, bool> class Storage = ET_STORAGE_TYPE
>
struct expression
        : functor<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        , private Storage<Left, Right, IsLeftRValRef, IsRightRValRef>
{
    using expression_type = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using storage_base_type = Storage<Left, Right, IsLeftRValRef, IsRightRValRef>;

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


// refer to http://en.cppreference.com/w/cpp/language/operator_precedence
#include "rocky/et/BinaryOperator.h"
#include "rocky/et/UnaryOperator.h"


#endif // ROCKY_ET_H
