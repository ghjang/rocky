#ifndef ROCKY_BASE_SWAP_H
#define ROCKY_BASE_SWAP_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct Swap
{
    static_assert(sizeof...(xs) == 2, "xs's length should be 2.");
};

template <typename x, typename y>
struct Swap<x, y> : type_is<TypeList<y, x>>
{ };


template <typename... xs>
using SwapT = typename Swap<xs...>::type;


template <template <typename...> class TypeListContainer, typename x, typename y>
struct Swap<TypeListContainer<x, y>>
        : ReplaceTypeListContainer<SwapT<x, y>, TypeListContainer>
{ };


#endif //ROCKY_BASE_SWAP_H

