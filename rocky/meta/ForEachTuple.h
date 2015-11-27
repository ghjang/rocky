#ifndef ROCKY_FOREACHTUPLEELEMENT_H
#define ROCKY_FOREACHTUPLEELEMENT_H


#include <tuple>
#include <utility>

#include "rocky/meta/ForEachArgument.h"


template <typename F, typename... Types, std::size_t... Indice>
decltype(auto) ForEachTupleElementImpl(F && f, std::tuple<Types...> && t, std::index_sequence<Indice...>)
{
    return ForEachArgument(std::forward<F>(f), std::get<Indice>(t)...);
};

template <typename F, typename... Types>
decltype(auto) ForEachTupleElement(F && f, std::tuple<Types...> && t)
{
    return ForEachTupleElementImpl(
                std::forward<F>(f),
                std::forward<std::tuple<Types...>>(t),
                std::index_sequence_for<Types...>()
            );
}


#endif //ROCKY_FOREACHTUPLEELEMENT_H

