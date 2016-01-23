#ifndef ROCKY_INTEGRALCONSTANTUTILITY_H
#define ROCKY_INTEGRALCONSTANTUTILITY_H


#include <type_traits>

#include "rocky/StringNumberConversion.h"
#include "rocky/meta/TypeSelection.h"


template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator + (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 + v2), v1 + v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator - (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 - v2), v1 - v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator * (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 * v2), v1 * v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator / (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<decltype(v1 / v2), v1 / v2>{}; }

template <typename T1, T1 v1, typename T2, T2 v2>
constexpr auto operator == (std::integral_constant<T1, v1>, std::integral_constant<T2, v2>)
{ return std::integral_constant<bool, v1 == v2>{}; }


/**
 * variable template for ease use of std::integral_constant.
 */
template <int i>
constexpr std::integral_constant<int, i> int_c{};


/**
 * user-defined literal
 */
template <char... s>
constexpr auto operator ""_c ()
{
    return std::integral_constant<
                    int,
                    CharArrayToInt<s...>()
            >{};
}


/**
 * type alias for ease use of std::integral_constant
 */
template <int i>
using int_c_t = std::integral_constant<int, i>;

template <bool condition>
using bool_c_t = std::integral_constant<bool, condition>;


template <typename lhs, typename rhs>
struct Plus;

template <typename T1, T1 v1, typename T2, T2 v2>
struct Plus<std::integral_constant<T1, v1>, std::integral_constant<T2, v2>>
            : std::integral_constant<decltype(v1 + v2), v1 + v2>
{ };


template <typename lhs, typename rhs>
struct Minus;

template <typename T1, T1 v1, typename T2, T2 v2>
struct Minus<std::integral_constant<T1, v1>, std::integral_constant<T2, v2>>
        : std::integral_constant<decltype(v1 - v2), v1 - v2>
{ };


template <typename lhs, typename rhs>
struct IntegralConstantMultiply;

template <typename T1, T1 v1, typename T2, T2 v2>
struct IntegralConstantMultiply<std::integral_constant<T1, v1>, std::integral_constant<T2, v2>>
        : std::integral_constant<decltype(v1 * v2), v1 * v2>
{ };


template <typename lhs, typename rhs>
struct IntegralConstantDivide;

template <typename T1, T1 v1, typename T2, T2 v2>
struct IntegralConstantDivide<std::integral_constant<T1, v1>, std::integral_constant<T2, v2>>
        : std::integral_constant<decltype(v1 / v2), v1 / v2>
{
    static_assert(v2 != 0, "v2 can't be 0.");
};


template <template <typename> class Predicate>
struct TypeToBoolConstantType
{
    template <typename T>
    struct Convert
            : std::conditional<
                    Predicate<T>::value,
                    std::true_type,
                    std::false_type
                >
    { };
};


#endif //ROCKY_INTEGRALCONSTANTUTILITY_H

