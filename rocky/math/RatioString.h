#ifndef ROCKY_BASE_RATIOSTRING_H
#define ROCKY_BASE_RATIOSTRING_H


#include <ratio>

#include "rocky/math/Abs.h"
#include "rocky/base/CharSequenceUtility.h"


template <std::intmax_t Num, std::intmax_t Denom>
constexpr auto ToConstExprString(std::ratio<Num, Denom>)
{
    constexpr bool isNegative = (Num < 0 && Denom > 0) || (Num > 0 && Denom < 0);
    using num_seq_t = typename MakeCharSequenceFromInteger<Abs(Num)>::type;
    using denum_seq_t = typename MakeCharSequenceFromInteger<Abs(Denom)>::type;
    using joined_seq_t = std::conditional_t<
                                isNegative,
                                typename JoinCharSequence<
                                                CharSequence<'-'>, num_seq_t ,CharSequence<'/'>, denum_seq_t
                                            >::type,
                                typename JoinCharSequence<
                                                num_seq_t ,CharSequence<'/'>, denum_seq_t
                                            >::type
                            >;
    return char_array_c<joined_seq_t>;
}


#endif //ROCKY_BASE_RATIOSTRING_H

