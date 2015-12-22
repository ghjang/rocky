#ifndef ROCKY_INTEGERDIGITS_H
#define ROCKY_INTEGERDIGITS_H


#include <vector>

#include "rocky/wolca/IntegerLength.h"


auto IntegerDigits(intmax_t n)
{
    if (n < 0) {
        n = -n;
    }
    auto len = IntegerLength(n);
    std::vector<uint8_t> digits(len);
    for (decltype(auto) i = len - 1; i > 0; --i) {
        digits[i] = n % 10;
        n /= 10;
    }
    digits[0] = n;
    return digits;
}


#endif //ROCKY_INTEGERDIGITS_H

