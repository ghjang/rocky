#ifndef ROCKY_EXTRACTTUPLE_H
#define ROCKY_EXTRACTTUPLE_H


#include <tuple>
#include <utility>


template <typename IndexSequence, typename Tuple>
struct ExtractElementType;

template <typename T, T... i, typename... list>
struct ExtractElementType<std::integer_sequence<T, i...>, std::tuple<list...>>
{
    using type = std::tuple<std::tuple_element_t<i, std::tuple<list...>>...>;
};


#endif //ROCKY_EXTRACTTUPLE_H

