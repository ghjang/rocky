#ifndef ROCKY_SKULL_LAST_H
#define ROCKY_SKULL_LAST_H


#include "rocky/meta/TypeList.h"
#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <typename... xs>
using Last = HeadT<DropT<sizeof...(xs) - 1, xs...>>;


#endif //ROCKY_SKULL_LAST_H

