#ifndef ROCKY_TUPLESIZE_H
#define ROCKY_TUPLESIZE_H


#include <type_traits>
#include <tuple>

#include "rocky/meta/Fold.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/NthTuple.h"


template <typename... list>
struct SumOfElementTypeSize
            : FoldRight<
                    IntegralConstantSum,
                    std::integral_constant<std::size_t, 0>,
                    std::integral_constant<std::size_t, sizeof(list)>...
                >::type
{ };

template <typename... list>
struct SumOfElementTypeSize<std::tuple<list...>> : SumOfElementTypeSize<list...>
{ };


#endif //ROCKY_TUPLESIZE_H

