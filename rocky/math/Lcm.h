#ifndef ROCKY_MATH_LCM_H
#define ROCKY_MATH_LCM_H


#include "rocky/math/Gcd.h"


template <typename a, typename b>
struct Lcm;

template <typename T, int a, int b>
struct Lcm<std::integral_constant<T, a>, std::integral_constant<T, b>>
        : std::integral_constant<T, a * (b / GCD<a, b>())>
{
    static_assert(GCD<a, b>() != 0, "GCD should not be zero.");
};


template <int a, int b>
using LCM = Lcm<std::integral_constant<int, a>, std::integral_constant<int, b>>;


#endif //ROCKY_MATH_LCM_H

