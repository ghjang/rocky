#ifndef ROCKY_SKULL_LENGTH_H
#define ROCKY_SKULL_LENGTH_H


#include "rocky/meta/TypeList.h"


template <typename... xs>
struct Length : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <typename... xs>
struct Length<TypeList<xs...>> : Length<xs...>
{ };

template <typename... xs>
struct Length<std::tuple<xs...>> : Length<xs...>
{ };


#endif //ROCKY_SKULL_LENGTH_H

