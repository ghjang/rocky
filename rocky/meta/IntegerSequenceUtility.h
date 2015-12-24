#ifndef ROCKY_INTEGERSEQUENCEUTILITY_H
#define ROCKY_INTEGERSEQUENCEUTILITY_H


#include <type_traits>
#include <utility>


template <std::size_t i, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequence
{
private:
    template <typename IndexSequence, template<std::size_t> class F>
    struct CustomIntegerSequenceImpl;

    template <std::size_t... index, template<std::size_t> class F>
    struct CustomIntegerSequenceImpl<std::index_sequence<index...>, F>
    {
        using type = std::integer_sequence<std::size_t, F<index>::value...>;
    };

public:
    using type = typename CustomIntegerSequenceImpl<std::make_index_sequence<i>, GeneratorFunc>::type;
};

template <std::size_t i, template<std::size_t> class GeneratorFunc>
using MakeCustomIntegerSequence = typename CustomIntegerSequence<i, GeneratorFunc>::type;


template <typename... Sequence>
struct JoinIntegerSequence;

template <typename T, T... lhs, T... rhs>
struct JoinIntegerSequence<std::integer_sequence<T, lhs...>, std::integer_sequence<T, rhs...>>
{
    using type = std::integer_sequence<T, lhs..., rhs...>;
};

template <typename T, typename U, T... lhs, U... rhs>
struct JoinIntegerSequence<std::integer_sequence<T, lhs...>, std::integer_sequence<U, rhs...>>
{
    static_assert(std::is_same<T, U>(), "T and U should be the same type.");
};

template <typename T, typename U, T... first, U... second, typename... list>
struct JoinIntegerSequence<std::integer_sequence<T, first...>, std::integer_sequence<U, second...>, list...>
{
    using type = typename JoinIntegerSequence<
                                typename JoinIntegerSequence<
                                                std::integer_sequence<T, first...>,
                                                std::integer_sequence<U, second...>
                                            >::type,
                                list...
                            >::type;
};


template <typename IntegerSequence>
struct IntegerSequenceLength;

template <typename T, std::size_t... i>
struct IntegerSequenceLength<std::integer_sequence<T, i...>>
            : std::integral_constant<T, sizeof...(i)>
{ };


#endif //ROCKY_INTEGERSEQUENCEUTILITY_H

