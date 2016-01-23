#ifndef ROCKY_TYPELIST_H
#define ROCKY_TYPELIST_H


#include <tuple>

#include "rocky/meta/Identity.h"


template <typename... xs>
struct TypeList
{ };


template <typename... xs>
struct TypeListSize : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <typename... xs>
struct TypeListSize<TypeList<xs...>> : TypeListSize<xs...>
{ };


template <typename T>
struct TypeListToTuple;

template <typename... xs>
struct TypeListToTuple<TypeList<xs...>> : type_is<std::tuple<xs...>>
{ };


template <typename... xs>
using TypeListToTupleT = typename TypeListToTuple<xs...>::type;


#endif //ROCKY_TYPELIST_H

