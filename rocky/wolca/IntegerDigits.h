#ifndef ROCKY_WOLCA_INTEGERDIGITS_H
#define ROCKY_WOLCA_INTEGERDIGITS_H


#include <cassert>
#include <vector>

#include "rocky/math/Abs.h"
#include "rocky/wolca/IntegerLength.h"


template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
auto IntegerDigits(T n)
{
    n = Abs(n);
    auto len = IntegerLength(n);
    std::vector<uint8_t> digits(len);
    for (decltype(auto) i = len - 1; i > 0; --i) {
        digits[i] = n % 10;
        n /= 10;
    }
    digits[0] = n;
    return digits;
}


/**
 * @param[in] digitIndex 1-based digit index
 */
template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr auto IntegerDigit(T n, uint8_t numOfDigit, uint8_t digitIndex)
{
    assert(digitIndex > 0);
    if (digitIndex <= 0) {
        throw std::logic_error(
                        "invalid digit index value. digit index should be greater than zero."
                );
    }
    assert(digitIndex <= numOfDigit);
    if (digitIndex > numOfDigit) {
        throw std::logic_error(
                        "invalid digit index value. digit index should be less or equal to the number of digits"
                );
    }
    T modNum = 1;
    for (uint8_t i = 0; i < digitIndex; ++i) {
        modNum *= 10;
    }
    n %= modNum;

    for (uint8_t i = 0; i < digitIndex - 1; ++i) {
        n /= 10;
    }

    return Abs(n);
}


/**
 * @param[in] DigitIndex 1-based digit index
 */
template <intmax_t N, std::size_t DigitIndex>
struct TIntegerDigit
{
    static_assert(DigitIndex <= IntegerLength(N) && DigitIndex > 0);
    static constexpr int8_t value = IntegerDigit(N, IntegerLength(N), DigitIndex);
};


/**
 * @param[in] DigitIndex 1-based digit index
 */
template <intmax_t N, std::size_t DigitIndex>
struct TIntegerDigitCharacter
{
    static_assert(DigitIndex <= IntegerLength(N) && DigitIndex > 0);
    static constexpr char value = '0' + TIntegerDigit<N, DigitIndex>::value;
};


#endif //ROCKY_WOLCA_INTEGERDIGITS_H

