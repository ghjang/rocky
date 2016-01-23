#ifndef ROCKY_TYPESIZE_H
#define ROCKY_TYPESIZE_H


#include "rocky/meta/TypeAt.h"
#include "rocky/skull/Sum.h"


template <typename... xs>
struct SumOfTypeSize : Sum<std::integral_constant<std::size_t, sizeof(xs)>...>
{ };

template <typename... xs>
struct SumOfTypeSize<TypeList<xs...>> : SumOfTypeSize<xs...>
{ };

template <typename... xs>
struct SumOfTypeSize<std::tuple<xs...>> : SumOfTypeSize<xs...>
{ };


template <int i, typename... xs>
struct NthTypeSize : int_c_t<sizeof(TypeAtT<i, xs...>)>
{ };

template <int i, typename... xs>
struct NthTypeSize<i, TypeList<xs...>> : NthTypeSize<i, xs...>
{ };

template <int i, typename... xs>
struct NthTypeSize<i, std::tuple<xs...>> : NthTypeSize<i, xs...>
{ };


#endif //ROCKY_TYPESIZE_H

