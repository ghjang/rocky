#ifndef ROCKY_BASE_FUNCTIONCOMPOSITION_H
#define ROCKY_BASE_FUNCTIONCOMPOSITION_H


#include <tuple>


namespace Detail
{
    template<typename... Functions>
    class Composer
    {
    private:
        using function_composite_t = std::tuple<Functions...>;

        function_composite_t functions_;

    private:
        template <int i>
        struct IsLastFunctionIndex
                : std::integral_constant<bool, i == std::tuple_size<function_composite_t>() - 1>
        { };

        template <int i, typename... Arguments>
        auto CallFunctionAt(std::false_type, Arguments &&... args)
        {
            return std::get<i>(functions_)(
                    CallFunctionAt<i + 1>(IsLastFunctionIndex<i + 1>(), std::forward<Arguments>(args)...)
            );
        }

        template <int i, typename... Arguments>
        auto CallFunctionAt(std::true_type, Arguments &&... args)
        {
            return std::get<i>(functions_)(std::forward<Arguments>(args)...);
        };

    public:
        template <typename... F>
        Composer(F &&... fs)
                : functions_{ std::forward<F>(fs)... }
        { }

    public:
        template <typename... Arguments>
        auto operator () (Arguments &&... args)
        {
            return CallFunctionAt<0>(IsLastFunctionIndex<0>(), std::forward<Arguments>(args)...);
        }
    };
} // namespace Detail


template <typename... F>
auto compose(F &&... fs)
{
    return Detail::Composer<std::decay_t<F>...>{ std::forward<F>(fs)... };
}


#endif //ROCKY_BASE_FUNCTIONCOMPOSITION_H

