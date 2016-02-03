#ifndef ROCKY_APP_COUNTIF_H
#define ROCKY_APP_COUNTIF_H


#include "rocky/skull/Sum.h"
#include "rocky/app/Transform.h"


template <template <typename> class p, typename... xs>
using CountIf = SumT<MapToBoolConstantTypeT<p, xs...>>;


#endif //ROCKY_APP_COUNTIF_H

