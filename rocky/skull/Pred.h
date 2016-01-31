#ifndef ROCKY_SKULL_PRED_H
#define ROCKY_SKULL_PRED_H


#include <type_traits>


template <typename IntegralConstant>
struct Pred;

template <typename T, T i>
struct Pred<std::integral_constant<T, i>> : std::integral_constant<T, i - 1>
{ };


template <int i>
using PredV = Pred<std::integral_constant<int, i>>;


#endif //ROCKY_SKULL_PRED_H

