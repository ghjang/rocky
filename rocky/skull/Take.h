#ifndef ROCKY_SKULL_TAKE_H
#define ROCKY_SKULL_TAKE_H


#include <type_traits>

#include "rocky/meta/TypeList.h"
#include "rocky/meta/TypeSelection.h"


template <std::size_t n, typename... T>
struct Take;

template <std::size_t n, typename... T>
using TakeT = typename Take<n, T...>::type;

template <std::size_t n>
struct Take<n> : type_is<TypeList<>>
{ };

template <std::size_t n, typename x, typename... xs>
struct Take<n, x, xs...>
            : type_is<
                    JoinTypeListT<
                            SelectTypeIfT<
                                    n == 0,
                                    TypeList<>,
                                    JoinTypeList<x, TakeT<n - 1, xs...>>
                            >,
                            TypeList<>
                    >
              >
{ };

template <std::size_t n, typename... xs>
struct Take<n, TypeList<xs...>> : Take<n, xs...>
{ };


#endif //ROCKY_SKULL_TAKE_H

