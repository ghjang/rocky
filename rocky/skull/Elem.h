#ifndef ROCKY_SKULL_ELEM_H
#define ROCKY_SKULL_ELEM_H


#include "rocky/meta/Find.h"


template <typename T, typename... xs>
struct Elem : std::integral_constant<bool, Find<T, xs...>::value != -1>
{ };


template <typename T, typename... xs>
struct Elem<T, TypeList<xs...>> : Elem<T, xs...>
{ };

template <typename T, typename... xs>
struct Elem<T, std::tuple<xs...>> : Elem<T, xs...>
{ };


#endif //ROCKY_SKULL_ELEM_H

