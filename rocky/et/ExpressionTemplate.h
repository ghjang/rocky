#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>
#include <type_traits>
#include <tuple>


struct left_shift
{
    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return std::forward<L>(l) << std::forward<R>(r);
    }
};


template <typename T>
struct terminal
{ };


template <std::size_t i>
struct placeholder
        : terminal<placeholder<i>>
        , std::integral_constant<std::size_t, i>
{ };

static placeholder<1> const _1{};
static placeholder<2> const _2{};
static placeholder<3> const _3{};


template <typename T>
struct context
{
    T & args_;
};


template <typename Derived>
struct callable
{
private:
    template <std::size_t i, typename R, typename Context>
    decltype(auto) call_impl(placeholder<i> const&, R && r, Context & c)
    {
        return Derived::apply(
                    std::get<i - 1>(c.args_),
                    std::forward<R>(r)
               );
    }

    template <typename L, std::size_t i, typename Context>
    decltype(auto) call_impl(L && l, placeholder<i> const&, Context & c)
    {
        return Derived::apply(
                    std::forward<L>(l),
                    std::get<i - 1>(c.args_)
               );
    }

    template <std::size_t i, std::size_t j, typename Context>
    decltype(auto) call_impl(placeholder<i> const&, placeholder<j> const&, Context & c)
    {
        return Derived::apply(
                    std::get<i - 1>(c.args_),
                    std::get<j - 1>(c.args_)
               );
    }

    template <typename T, typename R, typename Context>
    decltype(auto) call_impl(callable<T> & l, R && r, Context & c)
    {
        return Derived::apply(l(c), std::forward<R>(r));
    }

    template <typename L, typename T, typename Context>
    decltype(auto) call_impl(L && l, callable<T> & r, Context & c)
    {
        return Derived::apply(std::forward<L>(l), r(c));
    }

    template <typename T, typename U, typename Context>
    decltype(auto) call_impl(callable<T> & l, callable<U> & r, Context & c)
    {
        return Derived::apply(l(c), r(c));
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
        : callable<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
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

template <typename L, std::size_t i>
auto operator << (L && l, placeholder<i> const& r)
{
    return expression<
                L, left_shift, placeholder<i> const,
                std::is_rvalue_reference<L>::value,
                false
           >{ std::forward<L>(l), r };
}


#endif // ROCKY_ET_H
