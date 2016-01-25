#ifndef ROCKY_INTEGERSEQUENCEUTILITY_H
#define ROCKY_INTEGERSEQUENCEUTILITY_H


#include "rocky/skull/FoldL.h"


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
    using type = FoldLT<AppendIntegerSequence, init_seq_t, list...>;
};


template <typename IntegerSequence>
struct IntegerSequenceLength;

template <typename T, T... i>
struct IntegerSequenceLength<std::integer_sequence<T, i...>>
            : std::integral_constant<T, sizeof...(i)>
{ };


template <std::size_t i, typename IntegerSequence>
struct IntegerSequenceValue;

template <typename T, T n, T... list>
struct IntegerSequenceValue<0, std::integer_sequence<T, n, list...>>
{
    static constexpr T value = n;
};

template <typename T>
struct IntegerSequenceValue<0, std::integer_sequence<T>>
{
    static_assert(IntegerSequenceLength<std::integer_sequence<T>>() > 0, "empty integer sequence");
};

template <std::size_t i, typename T>
struct IntegerSequenceValue<i, std::integer_sequence<T>>
{
    static_assert(i != 0, "out of range index value");
};

template <std::size_t i, typename T, T n, T... list>
struct IntegerSequenceValue<i, std::integer_sequence<T, n, list...>>
            : IntegerSequenceValue<i - 1, std::integer_sequence<T, list...>>
{ };


template <typename BoolSequence>
struct InvertBoolSequence;

template <typename T, T... i>
struct InvertBoolSequence<std::integer_sequence<T, i...>>
{
    using type = std::integer_sequence<T, (!i)...>;
};


#endif //ROCKY_INTEGERSEQUENCEUTILITY_H

