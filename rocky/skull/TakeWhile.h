#ifndef ROCKY_SKULL_TAKEWHILE_H
#define ROCKY_SKULL_TAKEWHILE_H


#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


namespace Detail
{
    template <typename p, typename... xs>
    struct TakeWhileImpl;

    template <typename p>
    struct TakeWhileImpl<p> : type_is<TypeList<>>
    { };

    template <typename p, typename x, typename... xs>
    struct TakeWhileImpl<p, x, xs...>
            : FlattenAsTypeList<
                    SelectTypeIfT<
                            !ApplyT<p, x>(),
                            TypeList<>,
                            FlattenAsTypeList<x, typename TakeWhileImpl<p, xs...>::type>
                    >,
                    TypeList<>
            >
    {
        static_assert(HasValueMember<ApplyT<p, x>>(), "applied predicate 'p' should have 'value' member.");
    };
} // namespace Detail


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename... xs>
struct TakeWhile : Detail::TakeWhileImpl<p, xs...>
{ };


template <typename p, typename... xs>
using TakeWhileT = typename TakeWhile<p, xs...>::type;


template <typename p, template <typename...> class TypeListContainer, typename... xs>
struct TakeWhile<p, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<TakeWhileT<p, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_TAKEWHILE_H

