#ifndef ROCKY_INTEGERLENGTH_H
#define ROCKY_INTEGERLENGTH_H


#include <cstdint>


constexpr std::size_t IntegerLength(intmax_t i)
{
    if (i < 0) {
        i = -i;
    }
    if (i < 10) {
        return 1;
    }
    std::size_t n = 1;
    for ( ; ; ) {
        ++n;
        if (i / 10 < 10) {
            break;
        }
        i /= 10;
    }
    return n;
}


#endif //ROCKY_INTEGERLENGTH_H

