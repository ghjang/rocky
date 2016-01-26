#ifndef ROCKY_SKULL_NOT_H
#define ROCKY_SKULL_NOT_H


#include <type_traits>


template <typename T>
struct Not;

template <typename T, T i>
struct Not<std::integral_constant<T, i>> : std::integral_constant<T, !i>
{ };


#endif //ROCKY_SKULL_NOT_H

