#ifndef ROCKY_SKULL_INIT_H
#define ROCKY_SKULL_INIT_H


#include "rocky/base/TypeList.h"
#include "rocky/skull/Take.h"


template <typename... xs>
struct Init
{
    static_assert(sizeof...(xs) > 0, "empty type list is not allowed.");
};

/*
 * NOTE: following is not a valid codes.
 */
/*
template <typename... xs, typename x>
struct Init<xs..., x> : type_is<TypeList<xs...>>
{ };
 */

template <typename x, typename... xs>
struct Init<x, xs...> : Take<sizeof...(xs), x, xs...>
{ };


template <typename... xs>
using InitT = typename Init<xs...>::type;


template <template <typename...> class TypeListContainer, typename... xs>
struct Init<TypeListContainer<xs...>>
        : ReplaceTypeListContainer<InitT<xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_INIT_H

