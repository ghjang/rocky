#ifndef ROCKY_COUNT_H
#define ROCKY_COUNT_H


#include "rocky/meta/Transform.h"
#include "rocky/skull/Sum.h"


template <template <typename> class p, typename... xs>
using Count = SumT<MapToBoolConstantTypeT<p, xs...>>;


#endif //ROCKY_COUNT_H

