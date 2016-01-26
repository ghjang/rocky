#ifndef ROCKY_TRANSFORMINTEGERSEQUENCE_H
#define ROCKY_TRANSFORMINTEGERSEQUENCE_H


#include <type_traits>
#include <utility>

#include "rocky/base/HasMember.h"
#include "rocky/base/IntegerSequenceUtility.h"


namespace Detail
{
    template<template<std::size_t> class F, typename IntegerSequence, typename IndexSequence>
    struct TransformIntegerSequenceImpl;

    template<template<std::size_t> class F, typename T, T... list, std::size_t... i>
    struct TransformIntegerSequenceImpl<F, std::integer_sequence<T, list...>, std::index_sequence<i...>>
    {
        using type = std::integer_sequence<
                            T,
                            F<IntegerSequenceValueAt<i, std::integer_sequence<T, list...>>::value>::value...
                        >;
    };
} // namespace Detail


template <template <std::size_t> class F, typename IntegerSequence>
struct TransformIntegerSequence;

template <template <std::size_t> class F, typename T>
struct TransformIntegerSequence<F, std::integer_sequence<T>>
{
private:
    template <typename IntSeq>
    struct IntSeqLen;

    template <T... i>
    struct IntSeqLen<std::integer_sequence<T, i...>>
            : std::integral_constant<T, sizeof...(i)>
    { };

    static_assert(
            IntSeqLen<std::integer_sequence<T>>() > 0, "integer sequence should have at least one integer value."
    );
};

template <template <std::size_t> class F, typename T, T first, T... list>
struct TransformIntegerSequence<F, std::integer_sequence<T, first, list...>>
            : Detail::TransformIntegerSequenceImpl<
                    F,
                    std::integer_sequence<T, first, list...>,
                    std::make_index_sequence<1 + sizeof...(list)>
                >
{
    static_assert(HasValueMember<F<first>>(), "F should have 'value' member.");
};


template <template<std::size_t> class GeneratorFunc, std::size_t i>
using MakeCustomIntegerSequence = typename TransformIntegerSequence<
                                                GeneratorFunc,
                                                std::make_index_sequence<i>
                                            >::type;


#endif //ROCKY_TRANSFORMINTEGERSEQUENCE_H

