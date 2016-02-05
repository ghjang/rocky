#ifndef ROCKY_SKULL_TAKEWHILE_H
#define ROCKY_SKULL_TAKEWHILE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"


template <template <typename> class p, typename... xs>
struct TakeWhile;

template <template <typename> class p, typename... xs>
using TakeWhileT = typename TakeWhile<p, xs...>::type;

template <template <typename> class p>
struct TakeWhile<p> : type_is<TypeList<>>
{ };

template <template <typename> class p, typename x, typename... xs>
struct TakeWhile<p, x, xs...>
            : FlattenAsTypeList<
                    SelectTypeIfT<
                            !p<x>(),
                            TypeList<>,
                            FlattenAsTypeList<x, TakeWhileT<p, xs...>>
                    >,
                    TypeList<>
              >
{
    static_assert(HasValueMember<p<x>>(), "Predicate 'p' should have 'value' member.");
};

template <template <typename> class p, typename... xs>
struct TakeWhile<p, TypeList<xs...>> : TakeWhile<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct TakeWhile<p, std::tuple<xs...>> : TypeListToTuple<TakeWhileT<p, xs...>>
{ };


#endif //ROCKY_SKULL_TAKEWHILE_H

