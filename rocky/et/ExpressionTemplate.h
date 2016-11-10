#ifndef ROCKY_ET_H
#define ROCKY_ET_H


#include <utility>


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


template <typename Derived>
struct callable
{
private:
    template <std::size_t i, typename R, typename Args>
    decltype(auto) call_impl(placeholder<i> const&, R && r, Args & args)
    {
        return Derived::apply(
                    std::get<i - 1>(args),
                    std::forward<R>(r)
               );
    }    

    template <typename L, std::size_t i, typename Args>
    decltype(auto) call_impl(L && l, placeholder<i> const&, Args & args)
    {
        return Derived::apply(
                    std::forward<L>(l),
                    std::get<i - 1>(args)
               );
    }    

    template <std::size_t i, std::size_t j, typename Args>
    decltype(auto) call_impl(placeholder<i> const&, placeholder<j> const&, Args & args)
    {
        return Derived::apply(
                    std::get<i - 1>(args),
                    std::get<j - 1>(args)
               );
    }    

    template <typename T, typename R, typename Args>
    decltype(auto) call_impl(callable<T> & l, R && r, Args & args)
    {
        return Derived::apply(l(args), std::forward<R>(r));
    }    

    template <typename L, typename T, typename Args>
    decltype(auto) call_impl(L && l, callable<T> & r, Args & args)
    {
        return Derived::apply(std::forward<L>(l), r(args));
    }    

    template <typename T, typename U, typename Args>
    decltype(auto) call_impl(callable<T> & l, callable<U> & r, Args & args)
    {
        return Derived::apply(l(args), r(args));
    }

public:
    template <typename... Args>
    decltype(auto) operator () (std::tuple<Args...> & args)
    {
        return call_impl(derived()->left(), derived()->right(), args);
    }

    auto derived()
    {
        return static_cast<Derived *>(this);
    }

    template <typename... Args>
    decltype(auto) operator () (Args &&... args)
    {
        auto t = std::make_tuple(std::forward<Args>(args)...);
        return (*this)(t);
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

    template <typename R>
    auto operator << (R && r)
    {
        return expression<
                    expression_type, left_shift, std::decay_t<R>,
                    false,
                    std::is_rvalue_reference<decltype(r)>::value
               >{ *this, std::forward<R>(r) };
    }
};


template <typename L, std::size_t i>
auto operator << (L && l, placeholder<i> const& r)
{
    return expression<
                std::decay_t<L>, left_shift, placeholder<i> const,
                std::is_rvalue_reference<L>::value,
                false
           >{ std::forward<L>(l), r };
}


#endif // ROCKY_ET_H
