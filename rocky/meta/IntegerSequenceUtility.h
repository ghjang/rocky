#ifndef ROCKY_INTEGERSEQUENCEUTILITY_H
#define ROCKY_INTEGERSEQUENCEUTILITY_H


#include <utility>


template <typename IndexSequence, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequenceImpl;

template <std::size_t... i, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequenceImpl<
            std::index_sequence<i...>,
            GeneratorFunc
        >
{
    using type = std::integer_sequence<std::size_t, GeneratorFunc<i>::value...>;
};

template <std::size_t i, template<std::size_t> class GeneratorFunc>
struct CustomIntegerSequence
        : CustomIntegerSequenceImpl<std::make_index_sequence<i>, GeneratorFunc>
{ };

template <std::size_t i, template<std::size_t> class GeneratorFunc>
using MakeCustomIntegerSequence = typename CustomIntegerSequence<i, GeneratorFunc>::type;


#endif //ROCKY_INTEGERSEQUENCEUTILITY_H

