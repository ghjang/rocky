#ifndef ROCKY_SKULL_SND_H
#define ROCKY_SKULL_SND_H


#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <typename... xs>
struct Snd : Head<DropT<1, xs...>>
{
    static_assert(sizeof...(xs) == 2, "xs should be a type list of which length is 2.");
};

template <template <typename...> class TypeListContainer, typename x, typename y>
struct Snd<TypeListContainer<x, y>> : Snd<x, y>
{ };


template <typename... xs>
using SndT = typename Snd<xs...>::type;


#endif //ROCKY_SKULL_SND_H

