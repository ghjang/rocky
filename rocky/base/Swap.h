#ifndef ROCKY_BASE_SWAP_H
#define ROCKY_BASE_SWAP_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct Swap
{
    static_assert(sizeof...(xs) == 2, "xs's length should be 2.");
};

template <typename... xs>
using SwapT = typename Swap<xs...>::type;

template <typename x, typename y>
struct Swap<x, y> : type_is<TypeList<y, x>>
{ };


template <typename x, typename y>
struct Swap<TypeList<x, y>> : Swap<x, y>
{ };

template <typename x, typename y>
struct Swap<std::pair<x, y>> : type_is<std::pair<y, x>>
{ };

template <typename x, typename y>
struct Swap<std::tuple<x, y>> : ToTuple<SwapT<x, y>>
{ };


#endif //ROCKY_BASE_SWAP_H

