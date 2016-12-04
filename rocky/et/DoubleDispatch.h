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
    template <typename T, typename U>
    T * operator () (T * acc, else_final_t<U> & rhs)
    {
        if (acc != nullptr) {
            rhs.action_();
        }
        return acc;
    }

    template <typename T, typename Args>
    T * operator () (T * acc, Args && args)
    {
        if (acc == nullptr) {
            return nullptr;
        }
        if (acc->get_state() == std::get<0>(args)) {
            std::get<1>(args)(acc);
            acc->set_state(std::get<2>(args));
            return nullptr;
        }
        return acc;
    }
};

template <typename... Args>
auto if_condition(Args &&... args)
{
    static_assert(sizeof...(args) == 3);
    return std::make_tuple(std::forward<Args>(args)...);
}

template <typename Action>
auto else_final(Action && a)
{
    return else_final_t<std::decay_t<Action>>{ std::forward<Action>(a) };
}


#endif // ROCKY_ET_DOUBLE_DISPATCH_H
