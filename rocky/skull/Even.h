#ifndef ROCKY_SKULL_EVEN_H
#define ROCKY_SKULL_EVEN_H


#include "rocky/meta/IntegralConstantUtility.h"


template <typename T>
struct IsIntegralConstantType : std::false_type
{ };

template <typename T, T i>
struct IsIntegralConstantType<std::integral_constant<T, i>> : std::true_type
{ };


template <typename T>
struct Even
{
    static_assert(IsIntegralConstantType<T>(), "T should be std::integral_constant type.");
};

template <typename T, T i>
struct Even<std::integral_constant<T, i>> : std::integral_constant<bool, i % 2 == 0>
{ };


#endif //ROCKY_SKULL_EVEN_H

