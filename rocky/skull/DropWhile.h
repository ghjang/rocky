#ifndef ROCKY_SKULL_DROPWHILE_H
#define ROCKY_SKULL_DROPWHILE_H


#include "rocky/meta/TypeListFlatten.h"
#include "rocky/meta/TypeSelection.h"


template <template <typename> class p, typename... xs>
struct DropWhile;

template <template <typename> class p, typename... xs>
using DropWhileT = typename DropWhile<p, xs...>::type;


template <template <typename> class p>
struct DropWhile<p> : type_is<TypeList<>>
{ };


template <template <typename> class p, typename x, typename... xs>
struct DropWhile<p, x, xs...>
            : SelectTypeIf<
                    p<x>::value,
                    DropWhile<p, xs...>,
                    TypeList<x, xs...>
              >
{
    static_assert(HasValueMember<p<x>>(), "Predicate 'p' should have 'value' member.");
};


template <template <typename> class p, typename... xs>
struct DropWhile<p, TypeList<xs...>> : DropWhile<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct DropWhile<p, std::tuple<xs...>> : TypeListToTuple<DropWhileT<p, xs...>>
{ };


#endif //ROCKY_SKULL_DROPWHILE_H

