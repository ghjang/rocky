#ifndef ROCKY_SKULL_ALL_H
#define ROCKY_SKULL_ALL_H


#include "rocky/skull/Sum.h"
#include "rocky/skull/Map.h"


template <template <typename> class p, typename... xs>
struct All : std::integral_constant<bool, SumT<MapT<p, xs...>>() == sizeof...(xs)>
{ };

template <template <typename> class p>
struct All<p> : std::true_type
{ };


template <template <typename> class p, typename... xs>
struct All<p, TypeList<xs...>> : All<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct All<p, std::tuple<xs...>> : All<p, xs...>
{ };


#endif //ROCKY_SKULL_ALL_H

