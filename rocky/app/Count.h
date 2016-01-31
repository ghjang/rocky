#ifndef ROCKY_BASE_COUNT_H
#define ROCKY_BASE_COUNT_H


#include "rocky/skull/Sum.h"
#include "rocky/app/Transform.h"


template <template <typename> class p, typename... xs>
using Count = SumT<MapToBoolConstantTypeT<p, xs...>>;


#endif //ROCKY_BASE_COUNT_H

