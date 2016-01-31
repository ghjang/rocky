#ifndef ROCKY_BASE_COUNT_H
#define ROCKY_BASE_COUNT_H


#include "rocky/base/Transform.h"
#include "rocky/skull/Sum.h"


template <template <typename> class p, typename... xs>
using Count = SumT<MapToBoolConstantTypeT<p, xs...>>;


#endif //ROCKY_BASE_COUNT_H

