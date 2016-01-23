#ifndef ROCKY_COUNTTUPLE_H
#define ROCKY_COUNTTUPLE_H


#include "rocky/meta/Transform.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <template <typename> class Predicate, typename... list>
struct CountElementType
            : FoldRight<
                    IntegralConstantSum,
                    int_c_t<0>, // init
                    MapToBoolConstantTypeT<Predicate, std::tuple<list...>>
                >::type
{ };

template <template <typename> class Predicate, typename... list>
struct CountElementType<Predicate, std::tuple<list...>> : CountElementType<Predicate, list...>
{ };


#endif //ROCKY_COUNTTUPLE_H

