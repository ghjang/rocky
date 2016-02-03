#ifndef ROCKY_SKULL_MIN_H
#define ROCKY_SKULL_MIN_H


#include <type_traits>


template <typename T1, typename T2>
struct Min;

template <typename T, T v1, T v2>
struct Min<std::integral_constant<T, v1>, std::integral_constant<T, v2>>
        : std::integral_constant<T, (v1 > v2) ? v2 : v1>
{ };


#endif //ROCKY_SKULL_MIN_H

