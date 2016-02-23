#ifndef ROCKY_SKULL_TAKE_H
#define ROCKY_SKULL_TAKE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


namespace Detail
{
    template <std::size_t n, typename... xs>
    struct TakeImpl;

    template <std::size_t n>
    struct TakeImpl<n> : type_is<TypeList<>>
    { };

    template <std::size_t n, typename x, typename... xs>
    struct TakeImpl<n, x, xs...>
            : FlattenTypeList<
                    SelectTypeIfT<
                            n == 0,
                            TypeList<>,
                            FlattenTypeList<x, typename TakeImpl<n - 1, xs...>::type>
                    >,
                    TypeList<>
            >
    { };
} // namespace Detail


template <std::size_t n, typename... xs>
struct Take : Detail::TakeImpl<n, xs...>
{ };


template <std::size_t n, typename... xs>
using TakeT = typename Take<n, xs...>::type;


template <std::size_t n, template <typename...> class TypeListContainer, typename... xs>
struct Take<n, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<TakeT<n, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_TAKE_H

