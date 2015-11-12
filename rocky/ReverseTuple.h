#ifndef ROCKY_REVERSETUPLE_H
#define ROCKY_REVERSETUPLE_H


#include <tuple>

#include "NthTupleType.h"


template <typename Tuple, size_t sizeOfTuple, typename indexSequence>
struct ReverseTupleImpl;

template <typename... list, size_t sizeOfTuple, size_t... i>
struct ReverseTupleImpl<std::tuple<list...>, sizeOfTuple, std::index_sequence<i...>>
{
    using type = std::tuple<
                        typename NthTupleElementType<std::tuple<list...>, sizeOfTuple - i - 1>::type...
                    >;
};


template <typename Tuple>
struct ReverseTuple;

template <typename... list>
struct ReverseTuple<std::tuple<list...>>
{
    using type = typename ReverseTupleImpl<
                                std::tuple<list...>,
                                sizeof...(list),
                                std::make_index_sequence<sizeof...(list)>
                            >::type;
};


#endif //ROCKY_REVERSETUPLE_H

