#ifndef ROCKY_MATH_DIVISOR_H
#define ROCKY_MATH_DIVISOR_H


#include "rocky/base/TypeList.h"
#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/math/Abs.h"


namespace Detail
{
    template <typename... T>
    struct DivisorImpl;

    template <typename... xs, typename T, T i>
    struct DivisorImpl<TypeList<xs...>, std::integral_constant<T, i>, std::integral_constant<T, i>>
            : type_is<TypeList<xs..., std::integral_constant<T, i>>>
    { };

    template <typename... xs, typename T, T i, T j>
    struct DivisorImpl<TypeList<xs...>, std::integral_constant<T, i>, std::integral_constant<T, j>>
            : DivisorImpl<
                    std::conditional_t<
                            (i % j) == 0, // if divisor,
                            TypeList<xs..., std::integral_constant<T, j>>,
                            TypeList<xs...>
                    >,
                    std::integral_constant<T, i>,
                    std::integral_constant<T, j + 1>
              >
    { };
} // namespace Detail


template <typename T>
struct Divisor;

template <typename T>
struct Divisor<std::integral_constant<T, 0>>
        : type_is<TypeList<>>
{ };

template <typename T, T i>
struct Divisor<std::integral_constant<T, i>>
        : Detail::DivisorImpl<TypeList<>, std::integral_constant<T, Abs(i)>, std::integral_constant<T, 1>>
{ };


template <typename T>
using DivisorT = typename Divisor<T>::type;

template <int i>
using MakeDivisorTypeListT = DivisorT<int_c_t<i>>;


#endif //ROCKY_MATH_DIVISOR_H

