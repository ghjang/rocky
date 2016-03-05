#ifndef ROCKY_BASE_FOREACH_H
#define ROCKY_BASE_FOREACH_H


#include "rocky/base/ForEachArgument.h"
#include "rocky/base/TypeList.h"
#include "rocky/base/TypeUtility.h"


namespace Detail
{
    template <typename F, typename Tuple, std::size_t... Indice>
    decltype(auto) ForEachTupleElementImpl(F && f, Tuple && t, std::index_sequence<Indice...>)
    {
        return ForEachArgument(std::forward<F>(f), std::get<Indice>(std::forward<Tuple>(t))...);
    };
} // namespace Detail


template <typename F, typename... Types>
decltype(auto) ForEachElement(F && f, std::tuple<Types...> const& t)
{
    return Detail::ForEachTupleElementImpl(std::forward<F>(f), t, std::index_sequence_for<Types...>());
}

template <typename F, typename... Types>
decltype(auto) ForEachElement(F && f, std::tuple<Types...> && t)
{
    return Detail::ForEachTupleElementImpl(std::forward<F>(f), std::move(t), std::index_sequence_for<Types...>());
}


template <typename F, template <typename...> class TypeListContainer, typename... xs>
decltype(auto) ForEachElementType(F && f, TypeListContainer<xs...> &&)
{
    return ForEachArgument(std::forward<F>(f), type_c<xs>...);
}


#endif //ROCKY_BASE_FOREACH_H

