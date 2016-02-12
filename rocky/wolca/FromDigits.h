#ifndef ROCKY_WOLCA_FROMDIGITS_H
#define ROCKY_WOLCA_FROMDIGITS_H


#include "rocky/base/StringNumberConversion.h"
#include "rocky/skull/FoldL.h"


template <typename... xs>
struct FromDigits;

template <>
struct FromDigits<> : std::integral_constant<int, 0>
{ };

template <int... is>
struct FromDigits<std::integral_constant<int, is>...>
{
private:
    template <typename lhs, typename rhs>
    struct AppendDigitImpl;

    template <int lhs, int rhs>
    struct AppendDigitImpl<std::integral_constant<int, lhs>, std::integral_constant<int, rhs>>
            : std::integral_constant<int, lhs * 10 + rhs>
    { };

public :
    using type = FoldLT<Quote<AppendDigitImpl>, std::integral_constant<int, 0>, std::integral_constant<int, is>...>;
};

template <char... cs>
struct FromDigits<std::integral_constant<char, cs>...>
        : FromDigits<std::integral_constant<int, CharToInt(cs)>...>
{ };


template <int... is>
using FromDigitsT = typename FromDigits<std::integral_constant<int, is>...>::type;

template <char... cs>
using FromCharDigitsT = typename FromDigits<std::integral_constant<char, cs>...>::type;


#endif //ROCKY_WOLCA_FROMDIGITS_H

