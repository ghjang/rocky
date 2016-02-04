#ifndef ROCKY_WOLCA_FOLD_H
#define ROCKY_WOLCA_FOLD_H


#include "rocky/skull/FoldL.h"


template <template <typename, typename> class f, typename init, typename... xs>
using FoldT = typename FoldL<f, init, xs...>::type;


#endif //ROCKY_WOLCA_FOLD_H

