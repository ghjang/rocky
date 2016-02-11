#ifndef ROCKY_SKULL_ALL_H
#define ROCKY_SKULL_ALL_H


#include "rocky/skull/Sum.h"
#include "rocky/skull/Map.h"


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename... xs>
struct All : std::integral_constant<bool, SumT<MapT<p, xs...>>() == sizeof...(xs)>
{ };

template <typename p>
struct All<p> : std::true_type
{ };


template <typename p, typename... xs>
struct All<p, TypeList<xs...>> : All<p, xs...>
{ };

template <typename p, typename... xs>
struct All<p, std::tuple<xs...>> : All<p, xs...>
{ };


#endif //ROCKY_SKULL_ALL_H

