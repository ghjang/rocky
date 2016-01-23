#ifndef ROCKY_SKULL_DROP_H
#define ROCKY_SKULL_DROP_H


#include "rocky/meta/TypeList.h"
#include "rocky/meta/TypeSelection.h"


template <std::size_t n, typename... xs>
struct Drop;

template <std::size_t n, typename... xs>
using DropT = typename Drop<n, xs...>::type;

template <std::size_t n>
struct Drop<n> : type_is<TypeList<>>
{ };

template <std::size_t n, typename x, typename... xs>
struct Drop<n, x, xs...>
            : type_is<
                    JoinTypeListT<
                            SelectTypeIfT<
                                    n == 0,
                                    TypeList<x, xs...>,
                                    DropT<n - 1, xs...>
                            >,
                            TypeList<>
                    >
              >
{ };

template <std::size_t n, typename... xs>
struct Drop<n, TypeList<xs...>> : Drop<n, xs...>
{ };

template <std::size_t n, typename... xs>
struct Drop<n, std::tuple<xs...>> : TypeListToTuple<DropT<n, xs...>>
{ };


#endif //ROCKY_SKULL_DROP_H

