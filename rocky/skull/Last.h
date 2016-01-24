#ifndef ROCKY_SKULL_LAST_H
#define ROCKY_SKULL_LAST_H


#include "rocky/meta/TypeList.h"
#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <typename... xs>
struct Last : Head<DropT<(sizeof...(xs) <= 0) ? 0 : (sizeof...(xs) - 1), xs...>>
{ };


template <typename... xs>
using LastT = typename Last<xs...>::type;


template <typename... xs>
struct Last<TypeList<xs...>> : Last<xs...>
{ };

template <typename... xs>
struct Last<std::tuple<xs...>> : Last<xs...>
{ };


#endif //ROCKY_SKULL_LAST_H

