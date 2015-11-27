#ifndef ROCKY_FOREACHTUPLE_H
#define ROCKY_FOREACHTUPLE_H


#include <tuple>
#include <utility>

#include "rocky/meta/ForEachArgument.h"
#include "rocky/meta/TypeUtility.h"


template <typename F, typename... Types, std::size_t... Indice>
decltype(auto) ForEachElementImpl(F && f, std::tuple<Types...> && t, std::index_sequence<Indice...>)
{
    return ForEachArgument(std::forward<F>(f), std::get<Indice>(t)...);
};

template <typename F, typename... Types>
decltype(auto) ForEachElement(F && f, std::tuple<Types...> && t)
{
    return ForEachElementImpl(
                std::forward<F>(f),
                std::forward<std::tuple<Types...>>(t),
                std::index_sequence_for<Types...>()
            );
}


template <typename F, typename... Type>
decltype(auto) ForEachElementType(F && f, std::tuple<Type...> &&)
{
    return ForEachArgument(std::forward<F>(f), type_c<Type>...);
}


#endif //ROCKY_FOREACHTUPLE_H

