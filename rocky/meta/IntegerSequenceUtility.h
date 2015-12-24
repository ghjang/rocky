#ifndef ROCKY_INTEGERSEQUENCEUTILITY_H
#define ROCKY_INTEGERSEQUENCEUTILITY_H


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


#endif //ROCKY_INTEGERSEQUENCEUTILITY_H

