#ifndef ROCKY_WOLCA_INTEGERLENGTH_H
#define ROCKY_WOLCA_INTEGERLENGTH_H


#include <cstdint>
#include <type_traits>

#include "rocky/math/Abs.h"


template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr std::size_t IntegerLength(T i)
{
    i = Abs(i);
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


#endif //ROCKY_WOLCA_INTEGERLENGTH_H

