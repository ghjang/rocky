#ifndef ROCKY_INTEGERDIGITS_H
#define ROCKY_INTEGERDIGITS_H


#include <vector>

#include "rocky/wolca/IntegerLength.h"


template <typename T>
auto IntegerDigits(T n)
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

template <typename T>
constexpr auto Abs(T t)
{
    return (t < 0) ? -t : t;
}

constexpr auto IntegerDigit(intmax_t n, uint8_t numOfDigit, uint8_t digitIndex)
{
    intmax_t modNum = 1;
    for (uint8_t i = 0; i < digitIndex; ++i) {
        modNum *= 10;
    }
    n %= modNum;

    for (uint8_t i = 0; i < digitIndex - 1; ++i) {
        n /= 10;
    }

    return Abs(n);
}

template <intmax_t N, std::size_t DigitIndex>
struct IntegerDigitT
{
    static_assert(DigitIndex <= IntegerLength(N), "");
    static constexpr int8_t value = IntegerDigit(N, IntegerLength(N), DigitIndex);
};

template <intmax_t N, std::size_t DigitIndex>
struct IntegerDigitCharacterT
{
    static_assert(DigitIndex <= IntegerLength(N), "");
    static constexpr char value = '0' + IntegerDigitT<N, DigitIndex>::value;
};


#endif //ROCKY_INTEGERDIGITS_H

