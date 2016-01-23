#ifndef ROCKY_SKULL_SUM_H
#define ROCKY_SKULL_SUM_H


#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/FoldR.h"


template <typename... xs>
struct Sum;

template <typename T, T... i>
struct Sum<std::integral_constant<T, i>...>
        : FoldR<Plus, std::integral_constant<T, 0>, std::integral_constant<T, i>...>
{ };

template <typename... xs>
struct Sum<TypeList<xs...>> : Sum<xs...>
{ };

template <typename... xs>
struct Sum<std::tuple<xs...>> : Sum<xs...>
{ };


#endif //ROCKY_SKULL_SUM_H

