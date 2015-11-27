#ifndef ROCKY_NTHTUPLE_H
#define ROCKY_NTHTUPLE_H


/**
 * NOTE: prefer to use std::tuple_element over NthElementType.
 *       But it's an useful example for the variadic parameter pack looping.
 */


#include <type_traits>
#include <tuple>

#include "TypeSelection.h"
#include "Identity.h"


template <typename targetIndex, typename index, typename... list>
struct NthElementTypeImplLoop;

template <int targetIndex, int i, typename t>
struct NthElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t>
{
    using type = t;
};

template <int targetIndex, int i, typename t, typename... list>
struct NthElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t, list...>
        : SelectTypeIf<std::integral_constant<bool, targetIndex == i>,
                Identity<t>,
                NthElementTypeImplLoop<
                        std::integral_constant<int, targetIndex>,
                        std::integral_constant<int, i + 1>,
                        list...
                >
            >
{ };


template <typename Tuple, typename TargetIndex>
struct NthElementTypeImpl;

template <typename... list, int i>
struct NthElementTypeImpl<std::tuple<list...>, std::integral_constant<int, i>>
        : NthElementTypeImplLoop<
                std::integral_constant<int, i>,
                std::integral_constant<int, 0>,
                list...
            >
{
    static_assert(i >= 0 && i < sizeof...(list), "out of range tuple index");
};


template <typename Tuple, int i>
struct NthElementType
        : NthElementTypeImpl<
                Tuple,
                std::integral_constant<int, i>
            >
{ };


#endif //ROCKY_NTHTUPLE_H

