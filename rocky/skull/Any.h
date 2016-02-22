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


template <typename p, template <typename...> class TypeListContainer, typename... xs>
struct Any<p, TypeListContainer<xs...>> : Any<p, xs...>
{ };


#endif //ROCKY_SKULL_ANY_H

