#ifndef ROCKY_SKULL_NULL_H
#define ROCKY_SKULL_NULL_H


#include <type_traits>


template <typename... xs>
struct Null : std::false_type
{ };

template <>
struct Null<> : std::true_type
{ };


template <template <typename...> class TypeListContainer, typename... xs>
struct Null<TypeListContainer<xs...>> : Null<xs...>
{ };


#endif //ROCKY_SKULL_NULL_H

