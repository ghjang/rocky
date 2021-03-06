#ifndef ROCKY_SKULL_MAXIMUM_H
#define ROCKY_SKULL_MAXIMUM_H


#include "rocky/skull/FoldR.h"
#include "rocky/skull/Max.h"


template <typename... xs>
struct Maximum
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

template <typename T, T... i>
struct Maximum<std::integral_constant<T, i>...>
        : FoldR<
                Quote<Max>,
                std::integral_constant<T, std::numeric_limits<T>::min()>, // init
                std::integral_constant<T, i>...
            >
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Maximum<TypeListContainer<xs...>> : Maximum<xs...>
{ };


template <typename... xs>
using MaximumT = typename Maximum<xs...>::type;


#endif //ROCKY_SKULL_MAXIMUM_H

