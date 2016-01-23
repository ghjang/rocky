#ifndef ROCKY_SKULL_TAIL_H
#define ROCKY_SKULL_TAIL_H


#include <tuple>

#include "rocky/meta/Identity.h"
#include "rocky/meta/TypeListUtility.h"


template <typename... xs>
struct Tail
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

template <typename x, typename... xs>
struct Tail<x, xs...> : type_is<TypeList<xs...>>
{ };


template <typename... xs>
using TailT = typename Tail<xs...>::type;


template <typename... xs>
struct Tail<TypeList<xs...>> : Tail<xs...>
{ };

template <typename... xs>
struct Tail<std::tuple<xs...>> : TypeListToTuple<TailT<xs...>>
{ };


#endif //ROCKY_SKULL_TAIL_H

