#ifndef ROCKY_REVERSETUPLE_H
#define ROCKY_REVERSETUPLE_H


#include <tuple>


template <typename Tuple, size_t sizeOfTuple, typename IndexSequence>
struct ReverseElementTypeImpl;

template <typename... list, size_t sizeOfTuple, size_t... i>
struct ReverseElementTypeImpl<std::tuple<list...>, sizeOfTuple, std::index_sequence<i...>>
{
    using type = std::tuple<
                        std::tuple_element_t<sizeOfTuple - i - 1, std::tuple<list...>>...
                    >;
};


template <typename Tuple>
struct ReverseElementType;

template <typename... list>
struct ReverseElementType<std::tuple<list...>>
        : ReverseElementTypeImpl<
                std::tuple<list...>,
                sizeof...(list),
                std::index_sequence_for<list...>
            >
{ };


#endif //ROCKY_REVERSETUPLE_H

