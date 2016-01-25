#ifndef ROCKY_SKULL_FST_H
#define ROCKY_SKULL_FST_H


#include "rocky/meta/TypeList.h"
#include "rocky/skull/Head.h"


template <typename... xs>
struct Fst : Head<xs...>
{
    static_assert(sizeof...(xs) == 2, "xs should a type list of which length is 2.");
};


template <typename... xs>
using FstT = typename Fst<xs...>::type;


template <typename T1, typename T2>
struct Fst<TypeList<T1, T2>> : Fst<T1, T2>
{ };

template <typename T1, typename T2>
struct Fst<std::pair<T1, T2>> : Fst<T1, T2>
{ };

template <typename T1, typename T2>
struct Fst<std::tuple<T1, T2>> : Fst<T1, T2>
{ };


#endif //ROCKY_SKULL_FST_H

