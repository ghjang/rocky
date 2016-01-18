#ifndef ROCKY_SKULL_TAKE_H
#define ROCKY_SKULL_TAKE_H


#include <type_traits>

#include "rocky/meta/TypeList.h"
#include "rocky/meta/TypeSelection.h"


template <std::size_t n, typename... T>
struct Take;

template <std::size_t n>
struct Take<n> : type_is<TypeList<>>
{ };

template <std::size_t n, typename x, typename... xs>
struct Take<n, x, xs...>
            : type_is<
                    typename JoinTypeList<
                                typename SelectTypeIf<
                                                n == 0,
                                                TypeList<>,
                                                JoinTypeList<x, typename Take<n - 1, xs...>::type>
                                >::type,
                                TypeList<>
                    >::type
              >
{ };

template <std::size_t n, typename... xs>
struct Take<n, TypeList<xs...>> : Take<n, xs...>
{ };


#endif //ROCKY_SKULL_TAKE_H

