#ifndef ROCKY_CHARSEQUENCEUTILITY_H
#define ROCKY_CHARSEQUENCEUTILITY_H


#include "rocky/meta/IntegerSequenceUtility.h"
#include "rocky/wolca/IntegerDigits.h"


template <char... c>
using CharSequence = std::integer_sequence<char, c...>;


template <intmax_t n, typename IndexSequence>
struct MakeCharSequenceFromIntegerImpl;

template <intmax_t n, std::size_t... i>
struct MakeCharSequenceFromIntegerImpl<n, std::index_sequence<i...>>
{
    using type = std::conditional_t<
                        n < 0,
                        CharSequence<'-', IntegerDigitCharacterT<n, sizeof...(i) - i>::value...>,
                        CharSequence<IntegerDigitCharacterT<n, sizeof...(i) - i>::value...>
                    >;
};


template <intmax_t n>
struct MakeCharSequenceFromInteger
{
    using type = typename MakeCharSequenceFromIntegerImpl<
                                n,
                                std::make_index_sequence<IntegerLength(n)>
                            >::type;
};


#endif //ROCKY_CHARSEQUENCEUTILITY_H

