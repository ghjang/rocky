#ifndef ROCKY_BASE_TYPELISTFLATTEN_H
#define ROCKY_BASE_TYPELISTFLATTEN_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct FlattenTypeList;

template <>
struct FlattenTypeList<> : type_is<TypeList<>>
{ };

template <typename... xs>
struct FlattenTypeList<TypeList<xs...>> : type_is<TypeList<xs...>>
{ };

template <typename x>
struct FlattenTypeList<x> : type_is<TypeList<x>>
{ };

template <typename... xs, typename... ys, typename... zs>
struct FlattenTypeList<TypeList<xs...>, TypeList<ys...>, zs...>
        : FlattenTypeList<TypeList<xs..., ys...>, zs...>
{ };

template <typename... xs, typename y, typename... zs>
struct FlattenTypeList<TypeList<xs...>, y, zs...>
        : FlattenTypeList<TypeList<xs..., y>, zs...>
{ };

template <typename x, typename... ys, typename... zs>
struct FlattenTypeList<x, TypeList<ys...>, zs...>
        : FlattenTypeList<TypeList<x, ys...>, zs...>
{ };

template <typename x, typename y, typename... zs>
struct FlattenTypeList<x, y, zs...>
        : FlattenTypeList<TypeList<x, y>, zs...>
{ };


/**
 * NOTE: This will strip out all the outer type list containers.
 */
template <typename... xs>
struct FlattenTypeList<TypeList<TypeList<xs...>>> : FlattenTypeList<TypeList<xs...>>
{ };


template <typename... xs>
using FlattenTypeListT = typename FlattenTypeList<xs...>::type;


#endif //ROCKY_BASE_TYPELISTFLATTEN_H

