#ifndef ROCKY_SKULL_NEGATE_H
#define ROCKY_SKULL_NEGATE_H


#include <type_traits>


template <typename T>
struct Negate;

template <typename T, T i>
struct Negate<std::integral_constant<T, i>> : std::integral_constant<T, -i>
{ };


#endif //ROCKY_SKULL_NEGATE_H

