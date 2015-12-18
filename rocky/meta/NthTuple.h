#ifndef ROCKY_NTHTUPLE_H
#define ROCKY_NTHTUPLE_H


/**
 * NOTE: prefer to use std::tuple_element over NthElementType.
 *       But it's an useful example for the variadic parameter pack looping.
 */


#include <type_traits>
#include <tuple>

#include "rocky/meta/Identity.h"
#include "rocky/meta/IntegralConstantUtility.h"


template <typename TargetIndex, typename CurrentIndex, typename... list>
struct NthElementTypeImpl
{ };

template <int i, typename T, typename... list>
struct NthElementTypeImpl<int_c_t<i>, int_c_t<i>, T, list...> : type_is<T>
{ };

template <int i, int j, typename T, typename... list>
struct NthElementTypeImpl<int_c_t<i>, int_c_t<j>, T, list...> : NthElementTypeImpl<int_c_t<i>, int_c_t<j + 1>, list...>
{ };


template <int i, typename... list>
struct NthElementType : NthElementTypeImpl<int_c_t<i>, int_c_t<0>, list...>
{
    static_assert(i >= 0 && i < sizeof...(list), "out of range index: i");
};

template <int i, typename... list>
struct NthElementType<i, std::tuple<list...>> : NthElementType<i, list...>
{ };


#endif //ROCKY_NTHTUPLE_H

