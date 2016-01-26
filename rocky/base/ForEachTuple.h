#ifndef ROCKY_BASE_FOREACHTUPLE_H
#define ROCKY_BASE_FOREACHTUPLE_H


#include <tuple>
#include <utility>

#include "rocky/base/ForEachArgument.h"
#include "rocky/base/TypeUtility.h"


template <typename F, typename Tuple, std::size_t... Indice>
decltype(auto) ForEachElementImpl(F && f, Tuple && t, std::index_sequence<Indice...>)
{
    return ForEachArgument(std::forward<F>(f), std::get<Indice>(std::forward<Tuple>(t))...);
};

template <typename F, typename... Types>
decltype(auto) ForEachElement(F && f, std::tuple<Types...> const& t)
{
    return ForEachElementImpl(std::forward<F>(f), t, std::index_sequence_for<Types...>());
}

template <typename F, typename... Types>
decltype(auto) ForEachElement(F && f, std::tuple<Types...> && t)
{
    return ForEachElementImpl(std::forward<F>(f), std::move(t), std::index_sequence_for<Types...>());
}


template <typename F, typename... Type>
decltype(auto) ForEachElementType(F && f, std::tuple<Type...> &&)
{
    return ForEachArgument(std::forward<F>(f), type_c<Type>...);
}


#endif //ROCKY_BASE_FOREACHTUPLE_H

