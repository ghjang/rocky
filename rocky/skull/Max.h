#ifndef ROCKY_SKULL_MAX_H
#define ROCKY_SKULL_MAX_H


#include <type_traits>


template <typename T1, typename T2>
struct Max;

template <typename T, T v1, T v2>
struct Max<std::integral_constant<T, v1>, std::integral_constant<T, v2>>
        : std::integral_constant<T, (v1 > v2) ? v1 : v2>
{ };


#endif //ROCKY_SKULL_MAX_H

