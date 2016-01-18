#ifndef ROCKY_SKULL_TAIL_H
#define ROCKY_SKULL_TAIL_H


#include <tuple>

#include "rocky/meta/Identity.h"
#include "rocky/meta/TypeList.h"


template <typename... T>
struct Tail
{
    static_assert(sizeof...(T) > 0, "empty type list is not allowed.");
};

template <typename x, typename... xs>
struct Tail<x, xs...> : type_is<TypeList<xs...>>
{ };

template <typename... T>
struct Tail<std::tuple<T...>> : Tail<T...>
{ };


#endif //ROCKY_SKULL_TAIL_H

