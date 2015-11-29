#ifndef ROCKY_COUNTTUPLE_H
#define ROCKY_COUNTTUPLE_H


#include "rocky/meta/TransformTuple.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/Fold.h"


template <typename Tuple, template <typename> class Predicate>
struct CountElementType;

template <typename... list, template <typename> class Predicate>
struct CountElementType<std::tuple<list...>, Predicate>
            : FoldRight<
                    IntegralConstantSum,
                    std::integral_constant<int, 0>, // init
                    typename TransformElementTypeToBoolIntegralConstantType<
                                    std::tuple<list...>,
                                    Predicate
                                >::type
                >::type
{ };


#endif //ROCKY_COUNTTUPLE_H

