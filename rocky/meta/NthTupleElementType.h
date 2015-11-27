#ifndef ROCKY_NTHTUPLEELEMENTTYPE_H
#define ROCKY_NTHTUPLEELEMENTTYPE_H


/**
 * NOTE: prefer to use std::tuple_element over NthTupleElementType.
 *       But it's an useful example for the variadic parameter pack looping.
 */


#include <type_traits>
#include <tuple>

#include "TypeSelection.h"
#include "Identity.h"


template <typename targetIndex, typename index, typename... list>
struct NthTupleElementTypeImplLoop;

template <int targetIndex, int i, typename t>
struct NthTupleElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t>
{
    using type = t;
};

template <int targetIndex, int i, typename t, typename... list>
struct NthTupleElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t, list...>
        : SelectTypeIf<std::integral_constant<bool, targetIndex == i>,
                Identity<t>,
                NthTupleElementTypeImplLoop<
                        std::integral_constant<int, targetIndex>,
                        std::integral_constant<int, i + 1>,
                        list...
                >
            >
{ };


template <typename Tuple, typename TargetIndex>
struct NthTupleElementTypeImpl;

template <typename... list, int i>
struct NthTupleElementTypeImpl<std::tuple<list...>, std::integral_constant<int, i>>
        : NthTupleElementTypeImplLoop<
                std::integral_constant<int, i>,
                std::integral_constant<int, 0>,
                list...
            >
{
    static_assert(i >= 0 && i < sizeof...(list), "out of range tuple index");
};


template <typename Tuple, int i>
struct NthTupleElementType
        : NthTupleElementTypeImpl<
                Tuple,
                std::integral_constant<int, i>
            >
{ };


#endif //ROCKY_NTHTUPLEELEMENTTYPE_H

