#ifndef ROCKY_COUNT_H
#define ROCKY_COUNT_H


#include "rocky/meta/Transform.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <template <typename> class p, typename... xs>
struct Count
        : FoldRT<
                Plus,
                int_c_t<0>, // init
                MapToBoolConstantTypeT<p, xs...>
          >
{ };


#endif //ROCKY_COUNT_H

