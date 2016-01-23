#ifndef ROCKY_TUPLESIZE_H
#define ROCKY_TUPLESIZE_H


#include <type_traits>
#include <tuple>

#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/NthTuple.h"
#include "rocky/skull/FoldR.h"


template <typename... list>
struct SumOfElementTypeSize
            : FoldRT<
                    IntegralConstantSum,
                    std::integral_constant<std::size_t, 0>,
                    std::integral_constant<std::size_t, sizeof(list)>...
              >
{ };

template <typename... list>
struct SumOfElementTypeSize<std::tuple<list...>> : SumOfElementTypeSize<list...>
{ };


template <int i, typename... list>
struct NthElementTypeSize : int_c_t<sizeof(typename NthElementType<i, list...>::type)>
{ };

template <int i, typename... list>
struct NthElementTypeSize<i, std::tuple<list...>> : NthElementTypeSize<i, list...>
{ };


#endif //ROCKY_TUPLESIZE_H

