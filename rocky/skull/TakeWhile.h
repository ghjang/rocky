#ifndef ROCKY_SKULL_TAKEWHILE_H
#define ROCKY_SKULL_TAKEWHILE_H


#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename... xs>
struct TakeWhile;

template <typename p, typename... xs>
using TakeWhileT = typename TakeWhile<p, xs...>::type;

template <typename p>
struct TakeWhile<p> : type_is<TypeList<>>
{ };

template <typename p, typename x, typename... xs>
struct TakeWhile<p, x, xs...>
            : FlattenAsTypeList<
                    SelectTypeIfT<
                            !ApplyT<p, x>(),
                            TypeList<>,
                            FlattenAsTypeList<x, TakeWhileT<p, xs...>>
                    >,
                    TypeList<>
              >
{
    static_assert(HasValueMember<ApplyT<p, x>>(), "applied predicate 'p' should have 'value' member.");
};

template <typename p, typename... xs>
struct TakeWhile<p, TypeList<xs...>> : TakeWhile<p, xs...>
{ };

template <typename p, typename... xs>
struct TakeWhile<p, std::tuple<xs...>> : TypeListToTuple<TakeWhileT<p, xs...>>
{ };


#endif //ROCKY_SKULL_TAKEWHILE_H

