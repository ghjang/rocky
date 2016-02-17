#ifndef ROCKY_SKULL_DROPWHILE_H
#define ROCKY_SKULL_DROPWHILE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"
#include "rocky/base/TypeComposition.h"


/**
 * @tparam p predicate metafunction class
 * @tparam xs type list
 */
template <typename p, typename... xs>
struct DropWhile;

template <typename p, typename... xs>
using DropWhileT = typename DropWhile<p, xs...>::type;


template <typename p>
struct DropWhile<p> : type_is<TypeList<>>
{ };


template <typename p, typename x, typename... xs>
struct DropWhile<p, x, xs...>
            : SelectTypeIf<
                    ApplyT<p, x>::value,
                    DropWhile<p, xs...>,
                    TypeList<x, xs...>
              >
{
    static_assert(HasValueMember<ApplyT<p, x>>(), "applied predicate 'p' should have 'value' member.");
};


template <typename p, typename... xs>
struct DropWhile<p, TypeList<xs...>> : DropWhile<p, xs...>
{ };

template <typename p, typename... xs>
struct DropWhile<p, std::tuple<xs...>> : ToTuple<DropWhileT<p, xs...>>
{ };


#endif //ROCKY_SKULL_DROPWHILE_H

