#ifndef ROCKY_SKULL_NULL_H
#define ROCKY_SKULL_NULL_H


#include "rocky/meta/TypeList.h"


template <typename... xs>
struct Null : std::false_type
{ };

template <>
struct Null<> : std::true_type
{ };


template <typename... xs>
struct Null<TypeList<xs...>> : Null<xs...>
{ };

template <typename... xs>
struct Null<std::tuple<xs...>> : Null<xs...>
{ };


#endif //ROCKY_SKULL_NULL_H

