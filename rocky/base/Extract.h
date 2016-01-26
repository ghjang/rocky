#ifndef ROCKY_EXTRACT_H
#define ROCKY_EXTRACT_H


#include "rocky/base/TypeList.h"
#include "rocky/base/TypeAt.h"


template <typename IndexSequence, typename... xs>
struct Extract;

template <typename T, T... i, typename... xs>
struct Extract<std::integer_sequence<T, i...>, xs...>
        : type_is<TypeList<TypeAtT<i, xs...>...>>
{ };


template <typename T, typename... xs>
using ExtractT = typename Extract<T, xs...>::type;


template <typename T, T... i, typename... xs>
struct Extract<std::integer_sequence<T, i...>, TypeList<xs...>>
        : Extract<std::integer_sequence<T, i...>, xs...>
{ };

template <typename T, T... i, typename... xs>
struct Extract<std::integer_sequence<T, i...>, std::tuple<xs...>>
        : TypeListToTuple<ExtractT<std::integer_sequence<T, i...>, xs...>>
{ };


#endif //ROCKY_EXTRACT_H

