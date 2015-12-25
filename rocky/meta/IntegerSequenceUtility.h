#ifndef ROCKY_INTEGERSEQUENCEUTILITY_H
#define ROCKY_INTEGERSEQUENCEUTILITY_H


#include <type_traits>
#include <utility>

#include "rocky/meta/Fold.h"


template <typename... Sequence>
struct JoinIntegerSequence;

template <typename T, T... sequence, typename... list>
struct JoinIntegerSequence<std::integer_sequence<T, sequence...>, list...>
{
private:
    using init_seq_t = std::integer_sequence<T, sequence...>;

    template <typename LhsSeq, typename RhsSeq>
    struct AppendIntegerSequence;

    template <T... lhsSeq, T... rhsSeq>
    struct AppendIntegerSequence<std::integer_sequence<T, lhsSeq...>, std::integer_sequence<T, rhsSeq...>>
    {
        using type = std::integer_sequence<T, lhsSeq..., rhsSeq...>;
    };

    template <typename U, typename V, U... lhsSeq, V... rhsSeq>
    struct AppendIntegerSequence<std::integer_sequence<U, lhsSeq...>, std::integer_sequence<V, rhsSeq...>>
    {
        static_assert(std::is_same<U, V>(), "U and V should be the same type.");
    };

public:
    using type = typename FoldLeft<AppendIntegerSequence, init_seq_t, list...>::type;
};


template <typename IntegerSequence>
struct IntegerSequenceLength;

template <typename T, T... i>
struct IntegerSequenceLength<std::integer_sequence<T, i...>>
            : std::integral_constant<T, sizeof...(i)>
{ };


#endif //ROCKY_INTEGERSEQUENCEUTILITY_H

