#ifndef ROCKY_ET_DOUBLE_DISPATCH_H
#define ROCKY_ET_DOUBLE_DISPATCH_H


#include <tuple>

#include "rocky/et/Fold.h"


template <typename T>
struct else_final_t
{
    T action_;
};

struct if_t
{
    template <typename Lhs, typename T>
    auto operator () (Lhs && acc, else_final_t<T> & rhs)
    {
        if (acc != nullptr) {
            rhs.action_();
        }
        return acc;
    }

    template <typename Lhs, typename Rhs>
    std::decay_t<Lhs> operator () (Lhs && acc, Rhs && rhs)
    {
        if (acc == nullptr) {
            return nullptr;
        }
        if (acc->get_state() == std::get<0>(rhs)) {
            std::get<1>(rhs)(std::forward<Lhs>(acc));
            acc->set_state(std::get<2>(rhs));
            return nullptr;
        }
        return acc;
    }
};

template <typename... T>
auto if_condition(T &&... t)
{
    static_assert(sizeof...(t) == 3);
    return std::make_tuple(std::forward<T>(t)...);
}

template <typename T>
auto else_final(T && t)
{
    return else_final_t<std::decay_t<T>>{ std::forward<T>(t) };
}


#endif // ROCKY_ET_DOUBLE_DISPATCH_H
