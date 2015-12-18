#ifndef ROCKY_NTHTUPLE_H
#define ROCKY_NTHTUPLE_H


/**
 * NOTE: prefer to use std::tuple_element over NthElementType.
 *       But it's an useful example for the variadic parameter pack looping.
 */


#include <type_traits>
#include <tuple>

#include "rocky/meta/TypeSelection.h"
#include "rocky/meta/Identity.h"
#include "rocky/meta/IntegralConstantUtility.h"


template <typename targetIndex, typename index, typename... list>
struct NthElementTypeImplLoop;

template <int targetIndex, int i, typename t>
struct NthElementTypeImplLoop<int_c_t<targetIndex>, int_c_t<i>, t>
        : type_is<t>
{ };

template <int targetIndex, int i, typename t, typename... list>
struct NthElementTypeImplLoop<int_c_t<targetIndex>, int_c_t<i>, t, list...>
        : SelectTypeIf<
                targetIndex == i,
                type_is<t>,
                NthElementTypeImplLoop<int_c_t<targetIndex>, int_c_t<i + 1>, list...>
            >
{ };


template <typename Tuple, typename TargetIndex>
struct NthElementTypeImpl;

template <typename... list, int i>
struct NthElementTypeImpl<std::tuple<list...>, int_c_t<i>>
        : NthElementTypeImplLoop<int_c_t<i>, int_c_t<0>, list...>
{
    static_assert(i >= 0 && i < sizeof...(list), "out of range tuple index");
};


template <typename Tuple, int i>
struct NthElementType
        : NthElementTypeImpl<Tuple, int_c_t<i>>
{ };


#endif //ROCKY_NTHTUPLE_H

