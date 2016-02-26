#ifndef ROCKY_BASE_FUNCTIONARGUMENTBINDING_H
#define ROCKY_BASE_FUNCTIONARGUMENTBINDING_H


#include <tuple>


namespace Detail
{
    template <typename Function, typename... Arguments>
    class FirstBinder
    {
    private:
        using binding_args_t = std::tuple<Arguments...>;

        Function f_;
        binding_args_t args_;

    private:
        template <std::size_t... i, typename... Args>
        auto CallFunction(std::index_sequence<i...>, Args &&... args)
        {
            return f_(
                    std::get<i>(args_)..., // bind first
                    std::forward<Args>(args)...
            );
        }

    public:
        template <typename F, typename... Args>
        FirstBinder(F && f, Args &&... args)
                : f_{ std::forward<F>(f) }
                , args_{ std::forward<Args>(args)... }
        { }

    public:
        template <typename... Args>
        auto operator () (Args &&... args)
        {
            return CallFunction(
                    std::make_index_sequence<std::tuple_size<binding_args_t>::value>(), std::forward<Args>(args)...
            );
        }
    };

    template <typename Function, typename... Arguments>
    class LastBinder
    {
    private:
        using binding_args_t = std::tuple<Arguments...>;

        Function f_;
        binding_args_t args_;

    private:
        template <std::size_t... i, typename... Args>
        auto CallFunction(std::index_sequence<i...>, Args &&... args)
        {
            return f_(
                    std::forward<Args>(args)...,
                    std::get<i>(args_)... // bind last
            );
        }

    public:
        template <typename F, typename... Args>
        LastBinder(F && f, Args &&... args)
                : f_{ std::forward<F>(f) }
                , args_{ std::forward<Args>(args)... }
        { }

    public:
        template <typename... Args>
        auto operator () (Args &&... args)
        {
            return CallFunction(
                    std::make_index_sequence<std::tuple_size<binding_args_t>::value>(), std::forward<Args>(args)...
            );
        }
    };
} // namespace Detail


template <typename F, typename... Args>
auto bind_first(F && f, Args &&... args)
{
    return Detail::FirstBinder<std::decay_t<F>, std::decay_t<Args>...>(std::forward<F>(f), std::forward<Args>(args)...);
}

template <typename F, typename... Args>
auto bind_last(F && f, Args &&... args)
{
    return Detail::LastBinder<std::decay_t<F>, std::decay_t<Args>...>(std::forward<F>(f), std::forward<Args>(args)...);
}


#endif //ROCKY_BASE_FUNCTIONARGUMENTBINDING_H

