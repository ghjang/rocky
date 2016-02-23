#ifndef ROCKY_SKULL_DROP_H
#define ROCKY_SKULL_DROP_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


namespace Detail
{
    template <std::size_t n, typename... xs>
    struct DropImpl;

    template <std::size_t n>
    struct DropImpl<n> : type_is<TypeList<>>
    { };

    template <std::size_t n, typename x, typename... xs>
    struct DropImpl<n, x, xs...>
            : type_is<
                    FlattenTypeListT<
                            SelectTypeIfT<
                                    n == 0,
                                    TypeList<x, xs...>,
                                    DropImpl<n - 1, xs...>
                            >,
                            TypeList<>
                    >
            >
    { };
} // namespace Detail


template <std::size_t n, typename... xs>
struct Drop : Detail::DropImpl<n, xs...>
{ };


template <std::size_t n, typename... xs>
using DropT = typename Drop<n, xs...>::type;


template <std::size_t n, template <typename...> class TypeListContainer, typename... xs>
struct Drop<n, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<DropT<n, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_DROP_H

