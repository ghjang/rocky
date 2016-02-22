#ifndef ROCKY_SKULL_MINIMUM_H
#define ROCKY_SKULL_MINIMUM_H


#include "rocky/skull/FoldR.h"
#include "rocky/skull/Min.h"


template <typename... xs>
struct Minimum
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

template <typename T, T... i>
struct Minimum<std::integral_constant<T, i>...>
        : FoldR<
                Quote<Min>,
                std::integral_constant<T, std::numeric_limits<T>::max()>, // init
                std::integral_constant<T, i>...
        >
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Minimum<TypeListContainer<xs...>> : Minimum<xs...>
{ };


template <typename... xs>
using MinimumT = typename Minimum<xs...>::type;


#endif //ROCKY_SKULL_MINIMUM_H

