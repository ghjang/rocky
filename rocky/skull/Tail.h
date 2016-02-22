#ifndef ROCKY_SKULL_TAIL_H
#define ROCKY_SKULL_TAIL_H


#include "rocky/base/TypeList.h"


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


template <template <typename...> class TypeListContainer, typename... xs>
struct Tail<TypeListContainer<xs...>>
        : ReplaceTypeListContainer<TailT<xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_TAIL_H

