#ifndef ROCKY_MATH_GCD_H
#define ROCKY_MATH_GCD_H


namespace Detail
{
    template <typename a, typename b>
    struct GcdImpl;

    template <typename T, T a>
    struct GcdImpl<std::integral_constant<T, a>, std::integral_constant<T, 0>>
            : std::integral_constant<T, a>
    { };

    template <typename T, T a, T b>
    struct GcdImpl<std::integral_constant<T, a>, std::integral_constant<T, b>>
            : GcdImpl<std::integral_constant<T, b>, std::integral_constant<T, a % b>>
    { };
} // namespace Detail


template <typename a, typename b>
struct Gcd;

template <typename T>
struct Gcd<std::integral_constant<T, 0>, std::integral_constant<T, 0>>
        : std::integral_constant<T, 0>
{ };

template <typename T, T a>
struct Gcd<std::integral_constant<T, a>, std::integral_constant<T, 0>>
        : std::integral_constant<T, 0>
{ };

template <typename T, T a>
struct Gcd<std::integral_constant<T, 0>, std::integral_constant<T, a>>
        : std::integral_constant<T, 0>
{ };

template <typename T, T a, T b>
struct Gcd<std::integral_constant<T, a>, std::integral_constant<T, b>>
        : Detail::GcdImpl<std::integral_constant<T, b>, std::integral_constant<T, a % b>>
{ };


template <int a, int b>
using GCD = Gcd<std::integral_constant<int, a>, std::integral_constant<int, b>>;


#endif //ROCKY_MATH_GCD_H

