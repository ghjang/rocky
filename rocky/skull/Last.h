#ifndef ROCKY_SKULL_LAST_H
#define ROCKY_SKULL_LAST_H


#include "rocky/base/TypeList.h"
#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <typename... xs>
struct Last : Head<DropT<(sizeof...(xs) <= 0) ? 0 : (sizeof...(xs) - 1), xs...>>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Last<TypeListContainer<xs...>> : Last<xs...>
{ };


template <typename... xs>
using LastT = typename Last<xs...>::type;


#endif //ROCKY_SKULL_LAST_H

