#ifndef ROCKY_INTEGRALCONSTANTUTILITY_H
#define ROCKY_INTEGRALCONSTANTUTILITY_H


#include <type_traits>
#include <cassert>


template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator + (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 + v2), v1 + v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator - (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 - v2), v1 - v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator == (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<bool, v1 == v2>{}; }


/**
 * variable template for ease use of std::integral_constant.
 */
template <int i>
constexpr std::integral_constant<int, i> int_c{};


constexpr bool IsDigitChar(char c)
{
    static_assert('0' < '9', "'0' code value should be less than '9' one.");
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

template <char... s>
constexpr bool IsValidNumberFormat()
{
    constexpr char strArr[] = { s... };
    constexpr size_t len = sizeof...(s);
    size_t i = (strArr[0] == '-') ? 1 : 0;
    for ( ; i < len; ++i) {
        if (!IsDigitChar(strArr[i])) {
            return false;
        }
    }
    return true;
}

constexpr int CharToInt(char c)
{
    assert(IsDigitChar(c));
    if (!IsDigitChar(c)) {
        throw std::invalid_argument("c should be a valid digit char.");
    }
    return c - '0';
}

template <char... s>
constexpr int CharArrayToInt()
{
    static_assert(IsValidNumberFormat<s...>(), "s should be a valid number format string.");
    constexpr char strArr[] = { s... };
    constexpr size_t len = sizeof...(s);
    int val = 0;
    size_t i = (strArr[0] == '-') ? 1 : 0;
    for ( ; i < len; ++i) {
        int pow = 1;
        int n = len - i - 1;
        if (n > 0) {
            for (int j = 0; j < n; ++j) {
                pow *= 10;
            }
        }
        val += (CharToInt(strArr[i]) * pow);
    }
    return (strArr[0] == '-') ? -val : val;
}


template <char... s>
constexpr auto operator ""_c ()
{
    return std::integral_constant<
                    int,
                    CharArrayToInt<s...>()
            >{};
}


#endif //ROCKY_INTEGRALCONSTANTUTILITY_H

