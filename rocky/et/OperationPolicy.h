#ifndef ROCKY_ET_OPERATION_POLICY_H
#define ROCKY_ET_OPERATION_POLICY_H


//==============================================================================
template <typename T>
struct functor_context
{
    T & args_;
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
    decltype(auto) operator () (functor_context<T> & c)
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
        functor_context<decltype(t)> c{ t };
        return (*this)(c);
    }
};


//==============================================================================
template <typename F, typename T>
struct fold_functor_context
{
    F & bin_op_;
    T & args_;
};


template <typename Derived>
struct fold_functor
{
private:
    template <typename Lhs, typename Rhs, typename Context>
    decltype(auto) call_impl(Lhs & lhs, Rhs & rhs, Context & c)
    {
        // NOTE: ignore the Derived's OpTag.
        return c.bin_op_(lhs(c), rhs(c));
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

    template <typename F, typename T>
    decltype(auto) operator () (fold_functor_context<F, T> & c)
    {
        return call_impl(derived()->left(), derived()->right(), c);
    }

    template <typename F, typename T>
    decltype(auto) operator () (F && f, T && init)
    {
        auto t = std::make_tuple(
                        wrap(
                            std::forward<T>(init),
                            std::is_rvalue_reference<decltype(init)>()
                        )
                 );
        fold_functor_context<std::decay_t<F>, decltype(t)> c{ f, t };
        return (*this)(c);
    }
};


#endif // ROCKY_ET_OPERATION_POLICY_H
