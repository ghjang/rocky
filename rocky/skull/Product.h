#ifndef ROCKY_SKULL_PRODUCT_H
#define ROCKY_SKULL_PRODUCT_H


#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <typename... xs>
struct Product;

template <typename T, T... i>
struct Product<std::integral_constant<T, i>...>
        : type_is<FoldRT<Multiply, std::integral_constant<T, 1>, std::integral_constant<T, i>...>>
{ };


template <typename... xs>
using ProductT = typename Product<xs...>::type;


template <typename... xs>
struct Product<TypeList<xs...>> : Product<xs...>
{ };

template <typename... xs>
struct Product<std::tuple<xs...>> : Product<xs...>
{ };


#endif //ROCKY_SKULL_PRODUCT_H

