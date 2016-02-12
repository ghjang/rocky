#ifndef ROCKY_WOLCA_FOLD_H
#define ROCKY_WOLCA_FOLD_H


#include "rocky/skull/FoldL.h"


/**
 * @tparam f binary metafunction class
 */
template <typename f, typename init, typename... xs>
using FoldT = typename FoldL<f, init, xs...>::type;


#endif //ROCKY_WOLCA_FOLD_H

