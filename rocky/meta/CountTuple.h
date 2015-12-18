#ifndef ROCKY_COUNTTUPLE_H
#define ROCKY_COUNTTUPLE_H


#include "rocky/meta/TransformTuple.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/Fold.h"


template <template <typename> class Predicate, typename... list>
struct CountElementType : CountElementType<Predicate, std::tuple<list...>>
{ };

template <template <typename> class Predicate, typename... list>
struct CountElementType<Predicate, std::tuple<list...>>
            : FoldRight<
                    IntegralConstantSum,
                    int_c_t<0>, // init
                    typename TransformElementTypeToBoolConstantType<
                                    std::tuple<list...>,
                                    Predicate
                                >::type
                >::type
{ };


#endif //ROCKY_COUNTTUPLE_H

