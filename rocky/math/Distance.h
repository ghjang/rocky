#ifndef ROCKY_MATH_DISTANCE_H
#define ROCKY_MATH_DISTANCE_H


#include "rocky/math/Abs.h"


template <typename T1, typename T2>
inline constexpr auto Distance(T1 a1, T2 a2)
{
    return (Abs(a1) > Abs(a2)) ? Abs(a1 - a2) : Abs(a2 - a1);
}


template <typename T1, typename T2>
struct TDistance;

template <typename T1, T1 a1, typename T2, T2 a2>
struct TDistance<std::integral_constant<T1, a1>, std::integral_constant<T2, a2>>
        : std::integral_constant<decltype(a1 - a2), Distance(a1, a2)>
{ };


template <int a, int b>
using TDistanceT = TDistance<std::integral_constant<int, a>, std::integral_constant<int, b>>;


#endif //ROCKY_MATH_DISTANCE_H

