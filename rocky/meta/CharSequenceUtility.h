#ifndef ROCKY_CHARSEQUENCEUTILITY_H
#define ROCKY_CHARSEQUENCEUTILITY_H


#include "rocky/meta/IntegerSequenceUtility.h"
#include "rocky/wolca/IntegerDigits.h"


template <char... c>
using CharSequence = std::integer_sequence<char, c...>;


template <typename LhsSequence, typename RhsSequence>
using JoinCharSequence = JoinIntegerSequence<LhsSequence, RhsSequence>;


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
                            CharSequence<'-', IntegerDigitCharacterT<N, sizeof...(i) - i>::value...>,
                            CharSequence<IntegerDigitCharacterT<N, sizeof...(i) - i>::value...>
                        >;
    };

public:
    using type = typename MakeCharSequenceFromIntegerImpl<
                                n,
                                std::make_index_sequence<IntegerLength(n)>
                            >::type;
};


#endif //ROCKY_CHARSEQUENCEUTILITY_H

