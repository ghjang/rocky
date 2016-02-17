#ifndef ROCKY_SKULL_ANY_H
#define ROCKY_SKULL_ANY_H


#include "rocky/app/FindIf.h"


/**
 * @tparam p predicate metafunction class
 * @tparam xs type list
 */
template <typename p, typename... xs>
struct Any : std::integral_constant<bool, FindIf<p, xs...>() != -1>
{ };


template <typename p, typename... xs>
struct Any<p, TypeList<xs...>> : Any<p, xs...>
{ };

template <typename p, typename... xs>
struct Any<p, std::tuple<xs...>> : Any<p, xs...>
{ };


#endif //ROCKY_SKULL_ANY_H

