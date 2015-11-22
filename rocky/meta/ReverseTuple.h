#ifndef ROCKY_REVERSETUPLE_H
#define ROCKY_REVERSETUPLE_H


#include <tuple>


template <typename Tuple, size_t sizeOfTuple, typename indexSequence>
struct ReverseTupleImpl;

template <typename... list, size_t sizeOfTuple, size_t... i>
struct ReverseTupleImpl<std::tuple<list...>, sizeOfTuple, std::index_sequence<i...>>
{
    using type = std::tuple<
                        std::tuple_element_t<sizeOfTuple - i - 1, std::tuple<list...>>...
                    >;
};


template <typename Tuple>
struct ReverseTuple;

template <typename... list>
struct ReverseTuple<std::tuple<list...>>
        : ReverseTupleImpl<
                std::tuple<list...>,
                sizeof...(list),
                std::index_sequence_for<list...>
            >
{ };


#endif //ROCKY_REVERSETUPLE_H

