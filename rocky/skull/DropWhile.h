#ifndef ROCKY_SKULL_DROPWHILE_H
#define ROCKY_SKULL_DROPWHILE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"
#include "rocky/base/TypeComposition.h"


namespace Detail
{
    template <typename p, typename... xs>
    struct DropWhileImpl;

    template <typename p>
    struct DropWhileImpl<p> : type_is<TypeList<>>
    { };

    template <typename p, typename x, typename... xs>
    struct DropWhileImpl<p, x, xs...>
            : SelectTypeIf<
                    ApplyT<p, x>::value,
                    DropWhileImpl<p, xs...>,
                    TypeList<x, xs...>
              >
    {
        static_assert(HasValueMember<ApplyT<p, x>>(), "applied predicate 'p' should have 'value' member.");
    };
} // namespace Detail


/**
 * @tparam p predicate metafunction class
 * @tparam xs type list
 */
template <typename p, typename... xs>
struct DropWhile : Detail::DropWhileImpl<p, xs...>
{ };


template <typename p, typename... xs>
using DropWhileT = typename DropWhile<p, xs...>::type;


template <typename p, template <typename...> class TypeListContainer, typename... xs>
struct DropWhile<p, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<DropWhileT<p, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_DROPWHILE_H

