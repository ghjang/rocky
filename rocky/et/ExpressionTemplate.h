#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>
#include <type_traits>
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

    template <typename T>
    decltype(auto) operator () (context<T> & c)
    {
        return (*derived())(c);
    }
};


template <std::size_t i>
struct place_holder
        : terminal<place_holder<i>>
        , std::integral_constant<std::size_t, i>
{
    template <typename T>
    decltype(auto) operator () (context<T> & c)
    {
        return std::get<i - 1>(c.args_);
    }
};


static place_holder<1> _1{};
static place_holder<2> _2{};
static place_holder<3> _3{};


template
<
    typename Left, typename OpTag, typename Right,
    bool IsLeftRValRef, bool IsRightRValRef
>
struct expression;


template <typename Derived>
struct functor
{
private:
    template <typename T, typename Rhs, typename Context>
    decltype(auto) call_impl(terminal<T> & lhs, Rhs & rhs, Context & c)
    {
        return Derived::apply(lhs(c), rhs);
    }

    template <typename Lhs, typename T, typename Context>
    decltype(auto) call_impl(Lhs & lhs, terminal<T> & rhs, Context & c)
    {
        return Derived::apply(lhs, rhs(c));
    }

    template <typename T, typename U, typename Context>
    decltype(auto) call_impl(terminal<T> & lhs, terminal<U> & rhs, Context & c)
    {
        return Derived::apply(lhs(c), rhs(c));
    }

    template
    <
        typename Left, typename OpTag, typename Right,
        bool IsLeftRValRef, bool IsRightRValRef,
        typename R, typename Context
    >
    decltype(auto) call_impl(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                             R & rhs,
                             Context & c)
    {
        return Derived::apply(lhs(c), rhs);
    }

    template 
    <
        typename Left, typename OpTag, typename Right,
        bool IsLeftRValRef, bool IsRightRValRef,
        typename T, typename Context
    >
    decltype(auto) call_impl(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                             terminal<T> & t,
                             Context & c)
    {
        return Derived::apply(lhs(c), t(c));
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
        auto t = std::make_tuple(std::forward<Args>(args)...);
        context<decltype(t)> c{ t };
        return (*this)(c);
    }
};


template
<
    typename Left, typename Right,
    bool IsLeftRValRef, bool IsRightRValRef
>
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


template
<
    typename Left, typename OpTag, typename Right,
    bool IsLeftRValRef, bool IsRightRValRef
>
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


struct left_shift
{
    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return std::forward<L>(l) << std::forward<R>(r);
    }
};


template
<
    typename Left, typename OpTag, typename Right,
    bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto operator << (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs, Rhs && rhs)
{
    return expression<
                expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>, left_shift, Rhs,
                false,
                std::is_rvalue_reference<decltype(rhs)>::value
           >{ lhs, std::forward<Rhs>(rhs) };
}

template
<
    typename Left, typename OpTag, typename Right,
    bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto operator << (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs, Rhs && rhs)
{
    return expression<
                expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>, left_shift, Rhs,
                true,
                std::is_rvalue_reference<decltype(rhs)>::value
           >{ std::move(lhs), std::forward<Rhs>(rhs) };
}

template <typename Lhs, typename T>
auto operator << (Lhs && lhs, terminal<T> & rhs)
{
    return expression<
                Lhs, left_shift, T,
                std::is_rvalue_reference<Lhs>::value,
                false
           >{ std::forward<Lhs>(lhs), *(rhs.derived()) };
}

template <typename Lhs, typename T>
auto operator << (Lhs && lhs, terminal<T> && rhs)
{
    return expression<
                Lhs, left_shift, T,
                std::is_rvalue_reference<Lhs>::value,
                true
           >{ std::forward<Lhs>(lhs), std::move(*(rhs.derived())) };
}


#endif // ROCKY_ET_H
