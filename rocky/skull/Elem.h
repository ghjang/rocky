#ifndef ROCKY_SKULL_ELEM_H
#define ROCKY_SKULL_ELEM_H


#include "rocky/app/Find.h"


template <typename T, typename... xs>
struct Elem : std::integral_constant<bool, Find<T, xs...>::value != -1>
{ };


template <typename T, template <typename...> class TypeListContainer, typename... xs>
struct Elem<T, TypeListContainer<xs...>> : Elem<T, xs...>
{ };


#endif //ROCKY_SKULL_ELEM_H

