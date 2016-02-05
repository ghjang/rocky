#ifndef ROCKY_SKULL_TAKE_H
#define ROCKY_SKULL_TAKE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


template <std::size_t n, typename... xs>
struct Take;

template <std::size_t n, typename... xs>
using TakeT = typename Take<n, xs...>::type;

template <std::size_t n>
struct Take<n> : type_is<TypeList<>>
{ };

template <std::size_t n, typename x, typename... xs>
struct Take<n, x, xs...>
            : FlattenAsTypeList<
                    SelectTypeIfT<
                            n == 0,
                            TypeList<>,
                            FlattenAsTypeList<x, TakeT<n - 1, xs...>>
                    >,
                    TypeList<>
              >
{ };

template <std::size_t n, typename... xs>
struct Take<n, TypeList<xs...>> : Take<n, xs...>
{ };

template <std::size_t n, typename... xs>
struct Take<n, std::tuple<xs...>> : TypeListToTuple<TakeT<n, xs...>>
{ };


#endif //ROCKY_SKULL_TAKE_H

