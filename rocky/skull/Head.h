#ifndef ROCKY_SKULL_HEAD_H
#define ROCKY_SKULL_HEAD_H


#include "rocky/meta/TypeList.h"


template <typename... xs>
struct Head
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

template <typename x, typename... xs>
struct Head<x, xs...> : type_is<x>
{ };

template <typename... xs>
struct Head<TypeList<xs...>> : Head<xs...>
{ };

template <typename... xs>
struct Head<std::tuple<xs...>> : Head<xs...>
{ };


template <typename... xs>
using HeadT = typename Head<xs...>::type;


#endif //ROCKY_SKULL_HEAD_H

