#ifndef ROCKY_WOLCA_PADRIGHT_H
#define ROCKY_WOLCA_PADRIGHT_H


#include "rocky/skull/Take.h"
#include "rocky/skull/Replicate.h"
#include "rocky/skull/Concat.h"
#include "rocky/math/Distance.h"


template <typename n, typename x, typename... xs>
struct PadRight;

template <typename T, T n, typename x, typename... xs>
struct PadRight<std::integral_constant<T, n>, x, xs...>
        : SelectTypeIf<
                sizeof...(xs) >= n,
                Take<n, xs...>,
                Concat<
                        TypeList<xs...>,
                        ReplicateT<TDistanceT<n, sizeof...(xs)>::value, x>
                >
          >
{ };

template <typename T, T n, typename x, template <typename...> class TypeListContainer, typename... xs>
struct PadRight<std::integral_constant<T, n>, x, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<
                typename PadRight<std::integral_constant<T, n>, x, xs...>::type,
                TypeListContainer
          >
{ };


template <std::size_t n, typename x, typename... xs>
using PadRightT = typename PadRight<std::integral_constant<std::size_t, n>, x, xs...>::type;


#endif //ROCKY_WOLCA_PADRIGHT_H

