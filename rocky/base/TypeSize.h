#ifndef ROCKY_BASE_TYPESIZE_H
#define ROCKY_BASE_TYPESIZE_H


#include "rocky/base/TypeAt.h"
#include "rocky/skull/Sum.h"


template <typename... xs>
struct SumOfTypeSize : SumT<std::integral_constant<std::size_t, sizeof(xs)>...>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct SumOfTypeSize<TypeListContainer<xs...>> : SumOfTypeSize<xs...>
{ };


template <int i, typename... xs>
struct NthTypeSize : int_c_t<sizeof(TypeAtT<i, xs...>)>
{ };

template <int i, template <typename...> class TypeListContainer, typename... xs>
struct NthTypeSize<i, TypeListContainer<xs...>> : NthTypeSize<i, xs...>
{ };


#endif //ROCKY_BASE_TYPESIZE_H

