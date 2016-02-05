#ifndef ROCKY_WOLCA_PADLEFT_H
#define ROCKY_WOLCA_PADLEFT_H


#include "rocky/skull/Take.h"
#include "rocky/skull/Replicate.h"
#include "rocky/skull/Concat.h"
#include "rocky/math/Distance.h"


template <typename n, typename x, typename... xs>
struct PadLeft;

template <typename T, T n, typename x, typename... xs>
struct PadLeft<std::integral_constant<T, n>, x, xs...>
        : SelectTypeIf<
                sizeof...(xs) >= n,
                Take<n, xs...>,
                Concat<
                        ReplicateT<TDistanceT<n, sizeof...(xs)>::value, x>,
                        TypeList<xs...>
                >
        >
{ };

template <typename T, T n, typename x, typename... xs>
struct PadLeft<std::integral_constant<T, n>, x, TypeList<xs...>>
        : PadLeft<std::integral_constant<T, n>, x, xs...>
{ };


template <std::size_t n, typename x, typename... xs>
using PadLeftT = typename PadLeft<std::integral_constant<std::size_t, n>, x, xs...>::type;


#endif //ROCKY_WOLCA_PADLEFT_H

