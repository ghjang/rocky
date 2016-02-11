#ifndef ROCKY_SKULL_ITERATEN_H
#define ROCKY_SKULL_ITERATEN_H


#include "rocky/wolca/NestList.h"


/**
 * @tparam f metafunction class
 */
template <typename f, typename x, std::size_t n>
using IterateNT = NestListT<f, x, n>;


#endif //ROCKY_SKULL_ITERATEN_H

