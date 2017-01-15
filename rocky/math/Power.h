#ifndef ROCKY_MATH_POWER_H
#define ROCKY_MATH_POWER_H


#include <cassert>


constexpr int Power(int base, int n)
{
    assert(n >= 0);
    if (0 == n) {
        return 1;
    }
    int val = 1;
    for (int i = 0; i < n; ++i) {
        val *= base;
    }
    return val;
}


#endif //ROCKY_MATH_POWER_H

