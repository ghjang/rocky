#ifndef ROCKY_TUPLESIZE_H
#define ROCKY_TUPLESIZE_H


#include <type_traits>
#include <tuple>

#include "rocky/meta/FoldRight.h"
#include "rocky/meta/IntegralConstantUtility.h"


template <typename Tuple>
struct SumOfTupleElementTypeSize;

template <typename... list>
struct SumOfTupleElementTypeSize<std::tuple<list...>>
            : FoldRight<
                    IntegralConstantSum,
                    std::integral_constant<std::size_t, 0>,
                    std::integral_constant<std::size_t, sizeof(list)>...
                >::type
{ };


#endif //ROCKY_TUPLESIZE_H

