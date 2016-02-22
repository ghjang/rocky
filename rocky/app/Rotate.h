#ifndef ROCKY_APP_ROTATE_H
#define ROCKY_APP_ROTATE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"
#include "rocky/math/Abs.h"
#include "rocky/skull/Take.h"
#include "rocky/skull/Drop.h"


namespace Detail
{
    template <typename n, typename... xs>
    struct RotateImpl;

    template <typename T, T n>
    struct RotateImpl<std::integral_constant<T, n>> : type_is<TypeList<>>
    { };

    template <typename T, typename x, typename... xs>
    struct RotateImpl<std::integral_constant<T, 0>, x, xs...> : type_is<TypeList<x, xs...>>
    { };

    template <typename T, T i, typename... xs>
    struct RotateImpl<std::integral_constant<T, i>, xs...>
            : SelectTypeIf<
                    i < 0,
                    FlattenAsTypeList<
                            DropT<Abs(i) % sizeof...(xs), xs...>,
                            TakeT<Abs(i) % sizeof...(xs), xs...>
                    >, // left-rotation
                    FlattenAsTypeList<
                            DropT<sizeof...(xs) - (i % sizeof...(xs)), xs...>,
                            TakeT<sizeof...(xs) - (i % sizeof...(xs)), xs...>
                    > // right-rotation
              >
    { };
} // namespace Detail


template <typename n, typename... xs>
struct Rotate : Detail::RotateImpl<n, xs...>
{ };


template <typename n, typename... xs>
using RotateT = typename Rotate<n, xs...>::type;


template <typename T, T n, template <typename...> class TypeListContainer, typename... xs>
struct Rotate<std::integral_constant<T, n>, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<
                RotateT<std::integral_constant<T, n>, xs...>,
                TypeListContainer
          >
{ };


#endif //ROCKY_APP_ROTATE_H

