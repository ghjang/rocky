#ifndef ROCKY_SKULL_SUM_H
#define ROCKY_SKULL_SUM_H


#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <typename... xs>
struct Sum;

template <typename T, T... i>
struct Sum<std::integral_constant<T, i>...>
        : FoldR<Quote<Plus>, std::integral_constant<T, 0>, std::integral_constant<T, i>...>
{ };

template <template <typename...> class TypeListContainer, typename T, T... i>
struct Sum<TypeListContainer<std::integral_constant<T, i>...>>
        : Sum<std::integral_constant<T, i>...>
{ };


template <typename... xs>
using SumT = typename Sum<xs...>::type;


#endif //ROCKY_SKULL_SUM_H

