#ifndef ROCKY_SKULL_ODD_H
#define ROCKY_SKULL_ODD_H


#include "rocky/skull/Even.h"


template <typename T>
using Odd = std::integral_constant<bool, !Even<T>()>;


#endif //ROCKY_SKULL_ODD_H

