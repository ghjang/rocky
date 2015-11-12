#ifndef ROCKY_NTHTUPLEELEMENTTYPE_H
#define ROCKY_NTHTUPLEELEMENTTYPE_H


#include <type_traits>
#include <tuple>

#include "TypeSelection.h"
#include "WrapTypeMember.h"


template <typename targetIndex, typename index, typename... list>
struct NthTupleElementTypeImplLoop;

template <int targetIndex, int i, typename t>
struct NthTupleElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t>
{
    using type = t;
};

template <int targetIndex, int i, typename t, typename... list>
struct NthTupleElementTypeImplLoop<std::integral_constant<int, targetIndex>, std::integral_constant<int, i>, t, list...>
{
    using type = typename SelectTypeIf<std::integral_constant<bool, targetIndex == i>,
                                WrapAsTypeMember<t>,
                                NthTupleElementTypeImplLoop<
                                        std::integral_constant<int, targetIndex>,
                                        std::integral_constant<int, i + 1>,
                                        list...
                                >
                            >::type;
};


template <typename Tuple, typename TargetIndex>
struct NthTupleElementTypeImpl;

template <typename... list, int i>
struct NthTupleElementTypeImpl<std::tuple<list...>, std::integral_constant<int, i>>
{
    static_assert(i >= 0 && i < sizeof...(list), "out of range tuple index");
    using type = typename NthTupleElementTypeImplLoop<
                                std::integral_constant<int, i>,
                                std::integral_constant<int, 0>,
                                list...
                            >::type;
};


template <typename Tuple, int i>
struct NthTupleElementType
{
    using type = typename NthTupleElementTypeImpl<
                                Tuple,
                                std::integral_constant<int, i>
                            >::type;
};


#endif //ROCKY_NTHTUPLEELEMENTTYPE_H

