#ifndef ROCKY_SKULL_FST_H
#define ROCKY_SKULL_FST_H


#include "rocky/skull/Head.h"


template <typename... xs>
struct Fst : Head<xs...>
{
    static_assert(sizeof...(xs) == 2, "xs should be a type list of which length is 2.");
};

template <template <typename...> class TypeListContainer, typename x, typename y>
struct Fst<TypeListContainer<x, y>> : Fst<x, y>
{ };


template <typename... xs>
using FstT = typename Fst<xs...>::type;


#endif //ROCKY_SKULL_FST_H

