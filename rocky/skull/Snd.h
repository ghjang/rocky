#ifndef ROCKY_SKULL_SND_H
#define ROCKY_SKULL_SND_H


#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <typename... xs>
struct Snd : Head<DropT<1, xs...>>
{
    static_assert(sizeof...(xs) == 2, "xs should be a type list of which length is 2.");
};


template <typename... xs>
using SndT = typename Snd<xs...>::type;


template <typename T1, typename T2>
struct Snd<TypeList<T1, T2>> : Snd<T1, T2>
{ };

template <typename T1, typename T2>
struct Snd<std::pair<T1, T2>> : Snd<T1, T2>
{ };

template <typename T1, typename T2>
struct Snd<std::tuple<T1, T2>> : Snd<T1, T2>
{ };


#endif //ROCKY_SKULL_SND_H

