#ifndef ROCKY_SKULL_MAP_H
#define ROCKY_SKULL_MAP_H


#include "rocky/base/TypeList.h"
#include "rocky/base/HasMember.h"
#include "rocky/skull/Head.h"


template <template <typename> class f, typename... xs>
struct Map : type_is<TypeList<typename f<xs>::type...>>
{
    static_assert(HasTypeMember<f<HeadT<xs...>>>(), "f should have 'type' member.");
};

template <template <typename> class f>
struct Map<f> : type_is<TypeList<>>
{ };


template <template <typename> class f, typename... xs>
using MapT = typename Map<f, xs...>::type;


template <template <typename> class f, typename... xs>
struct Map<f, TypeList<xs...>> : Map<f, xs...>
{ };

template <template <typename> class f, typename... xs>
struct Map<f, std::tuple<xs...>> : TypeListToTuple<MapT<f, xs...>>
{ };


#endif //ROCKY_SKULL_MAP_H

