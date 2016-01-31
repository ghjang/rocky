#ifndef ROCKY_APP_ROTATE_H
#define ROCKY_APP_ROTATE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"
#include "rocky/math/Abs.h"
#include "rocky/skull/Take.h"
#include "rocky/skull/Drop.h"


template <typename n, typename... xs>
struct Rotate;

template <typename T, T n>
struct Rotate<std::integral_constant<T, n>> : type_is<TypeList<>>
{ };

template <typename T, typename x, typename... xs>
struct Rotate<std::integral_constant<T, 0>, x, xs...> : type_is<TypeList<x, xs...>>
{ };

template <typename T, T i, typename... xs>
struct Rotate<std::integral_constant<T, i>, xs...>
        : SelectTypeIf<
                i < 0,
                FlattenTypeList<
                        DropT<Abs(i) % sizeof...(xs), xs...>,
                        TakeT<Abs(i) % sizeof...(xs), xs...>
                >, // left-rotation
                FlattenTypeList<
                        DropT<sizeof...(xs) - (i % sizeof...(xs)), xs...>,
                        TakeT<sizeof...(xs) - (i % sizeof...(xs)), xs...>
                > // right-rotation
          >
{ };


template <typename n, typename... xs>
using RotateT = typename Rotate<n, xs...>::type;


template <typename T, T n, typename... xs>
struct Rotate<std::integral_constant<T, n>, TypeList<xs...>>
        : Rotate<std::integral_constant<T, n>, xs...>
{ };

template <typename T, T n, typename... xs>
struct Rotate<std::integral_constant<T, n>, std::tuple<xs...>>
        : TypeListToTuple<RotateT<std::integral_constant<T, n>, xs...>>
{ };


#endif //ROCKY_APP_ROTATE_H

