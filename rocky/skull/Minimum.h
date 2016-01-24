#ifndef ROCKY_SKULL_MINIMUM_H
#define ROCKY_SKULL_MINIMUM_H


#include "rocky/meta/TypeList.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <typename... xs>
struct Minimum
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

template <typename T, T... i>
struct Minimum<std::integral_constant<T, i>...>
        : FoldR<
                Min,
                std::integral_constant<T, std::numeric_limits<T>::max()>, // init
                std::integral_constant<T, i>...
        >
{ };


template <typename... xs>
using MinimumT = typename Minimum<xs...>::type;


template <typename... xs>
struct Minimum<TypeList<xs...>> : Minimum<xs...>
{ };

template <typename... xs>
struct Minimum<std::tuple<xs...>> : Minimum<xs...>
{ };


#endif //ROCKY_SKULL_MINIMUM_H

