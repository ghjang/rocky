#ifndef ROCKY_SKULL_SUCC_H
#define ROCKY_SKULL_SUCC_H


#include <type_traits>


template <typename IntegralConstant>
struct Succ;

template <typename T, T i>
struct Succ<std::integral_constant<T, i>> : std::integral_constant<T, i + 1>
{ };


template <int i>
using SuccV = Succ<std::integral_constant<int, i>>;


#endif //ROCKY_SKULL_SUCC_H

