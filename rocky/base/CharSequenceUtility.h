#ifndef ROCKY_BASE_CHARSEQUENCEUTILITY_H
#define ROCKY_BASE_CHARSEQUENCEUTILITY_H


#include "rocky/base/IntegerSequenceUtility.h"
#include "rocky/wolca/IntegerDigits.h"


template <char... c>
using CharSequence = std::integer_sequence<char, c...>;


template <typename... Sequence>
using JoinCharSequence = JoinIntegerSequence<Sequence...>;


template <typename CharSequence>
using CharSequenceLength = IntegerSequenceLength<CharSequence>;


template <typename CharSequence, std::size_t N = CharSequenceLength<CharSequence>::value>
static constexpr char char_array_c[N + 1];

template <char... c>
static constexpr char char_array_c<CharSequence<c...>, sizeof...(c)>[sizeof...(c) + 1] = { c..., '\0'};


template <intmax_t n>
struct MakeCharSequenceFromInteger
{
private:
    template <intmax_t N, typename IndexSequence>
    struct MakeCharSequenceFromIntegerImpl;

    template <intmax_t N, std::size_t... i>
    struct MakeCharSequenceFromIntegerImpl<N, std::index_sequence<i...>>
    {
        using type = std::conditional_t<
                            N < 0,
                            CharSequence<'-', TIntegerDigitCharacter<N, sizeof...(i) - i>::value...>,
                            CharSequence<TIntegerDigitCharacter<N, sizeof...(i) - i>::value...>
                        >;
    };

public:
    using type = typename MakeCharSequenceFromIntegerImpl<
                                n,
                                std::make_index_sequence<IntegerLength(n)>
                            >::type;
};


template <intmax_t n>
constexpr auto ToConstExprString()
{
    return char_array_c<typename MakeCharSequenceFromInteger<n>::type>;
}


#endif //ROCKY_BASE_CHARSEQUENCEUTILITY_H

