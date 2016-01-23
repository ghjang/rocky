#ifndef ROCKY_COUNTTUPLE_H
#define ROCKY_COUNTTUPLE_H


#include "rocky/meta/Transform.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <template <typename> class Predicate, typename... list>
struct CountElementType
            : FoldRT<
                    IntegralConstantSum,
                    int_c_t<0>, // init
                    MapToBoolConstantTypeT<Predicate, std::tuple<list...>>
              >
{ };

template <template <typename> class Predicate, typename... list>
struct CountElementType<Predicate, std::tuple<list...>> : CountElementType<Predicate, list...>
{ };


#endif //ROCKY_COUNTTUPLE_H

