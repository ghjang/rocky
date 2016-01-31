#ifndef ROCKY_SKULL_ANY_H
#define ROCKY_SKULL_ANY_H


#include "rocky/app/FindIf.h"


template <template <typename> class p, typename... xs>
struct Any : std::integral_constant<bool, FindIf<p, xs...>() != -1>
{ };


template <template <typename> class p, typename... xs>
struct Any<p, TypeList<xs...>> : Any<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct Any<p, std::tuple<xs...>> : Any<p, xs...>
{ };


#endif //ROCKY_SKULL_ANY_H

