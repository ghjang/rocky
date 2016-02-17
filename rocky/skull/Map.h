#ifndef ROCKY_SKULL_MAP_H
#define ROCKY_SKULL_MAP_H


#include "rocky/base/TypeList.h"
#include "rocky/base/TypeUtility.h"
#include "rocky/base/HasMember.h"
#include "rocky/skull/Head.h"


/**
 * @tparam f metafunction class
 */
template <typename f, typename... xs>
struct Map
{
    static_assert(HasTypeMember<Apply<f, HeadT<xs...>>>(), "applied f should have 'type' member.");

    using type = TypeList<ApplyT<f, xs>...>;
};

template <typename f>
struct Map<f> : type_is<TypeList<>>
{ };


template <typename f, typename... xs>
using MapT = typename Map<f, xs...>::type;


template <typename f, typename... xs>
struct Map<f, TypeList<xs...>> : Map<f, xs...>
{ };

template <typename f, typename... xs>
struct Map<f, std::tuple<xs...>> : ToTuple<MapT<f, xs...>>
{ };


#endif //ROCKY_SKULL_MAP_H

