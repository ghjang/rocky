#ifndef ROCKY_SKULL_SPLITAT_H
#define ROCKY_SKULL_SPLITAT_H


#include "rocky/base/TypeList.h"
#include "rocky/base/TypeSelection.h"


namespace Detail
{
    template <typename... xs>
    struct SplitAtImpl;

    template <typename... rs, typename T, T i>
    struct SplitAtImpl<TypeList<rs...>, std::integral_constant<T, i>>
                : type_is<TypeList<rs...>>
    { };

    template <typename... rs, typename T, T i, typename x, typename... xs>
    struct SplitAtImpl<TypeList<rs...>, std::integral_constant<T, i>, x, xs...>
                : SelectTypeIf<
                        (i - 1) == 0,
                        TypeList<TypeList<rs..., x>, TypeList<xs...>>,
                        SplitAtImpl<TypeList<rs..., x>, std::integral_constant<T, i - 1>, xs...>
                  >
    { };
}


template <typename i, typename... xs>
struct SplitAt;

template <typename T, T i>
struct SplitAt<std::integral_constant<T, i>>
        : type_is<TypeList<TypeList<>, TypeList<>>>
{
    static_assert(i >= 0, "i should be greater or equal to zero.");
};

template <typename T, typename x, typename... xs>
struct SplitAt<std::integral_constant<T, 0>, x, xs...>
        : type_is<TypeList<TypeList<>, TypeList<x, xs...>>>
{ };

template <typename T, T i, typename... xs>
struct SplitAt<std::integral_constant<T, i>, xs...>
        : Detail::SplitAtImpl<TypeList<>, std::integral_constant<T, i>, xs...>
{
    static_assert(i >= 0, "i should be greater or equal to zero.");
};


template <typename i, typename... xs>
using SplitAtT = typename SplitAt<i, xs...>::type;


template <typename T, T i, template <typename...> class TypeListContainer, typename... xs>
struct SplitAt<std::integral_constant<T, i>, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<SplitAtT<std::integral_constant<T, i>, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_SPLITAT_H

