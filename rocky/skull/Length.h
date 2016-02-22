#ifndef ROCKY_SKULL_LENGTH_H
#define ROCKY_SKULL_LENGTH_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct Length : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Length<TypeListContainer<xs...>> : Length<xs...>
{ };


#endif //ROCKY_SKULL_LENGTH_H

