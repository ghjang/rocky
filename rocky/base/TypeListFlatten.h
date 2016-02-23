#ifndef ROCKY_BASE_TYPELISTFLATTEN_H
#define ROCKY_BASE_TYPELISTFLATTEN_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct FlattenAsTypeList;

template <>
struct FlattenAsTypeList<> : type_is<TypeList<>>
{ };

template <typename... xs>
struct FlattenAsTypeList<TypeList<xs...>> : type_is<TypeList<xs...>>
{ };

template <typename x>
struct FlattenAsTypeList<x> : type_is<TypeList<x>>
{ };

template <typename... xs, typename... ys, typename... zs>
struct FlattenAsTypeList<TypeList<xs...>, TypeList<ys...>, zs...>
        : FlattenAsTypeList<TypeList<xs..., ys...>, zs...>
{ };

template <typename... xs, typename y, typename... zs>
struct FlattenAsTypeList<TypeList<xs...>, y, zs...>
        : FlattenAsTypeList<TypeList<xs..., y>, zs...>
{ };

template <typename x, typename... ys, typename... zs>
struct FlattenAsTypeList<x, TypeList<ys...>, zs...>
        : FlattenAsTypeList<TypeList<x, ys...>, zs...>
{ };

template <typename x, typename y, typename... zs>
struct FlattenAsTypeList<x, y, zs...>
        : FlattenAsTypeList<TypeList<x, y>, zs...>
{ };


/**
 * NOTE: This will strip out all the outer type list containers.
 */
template <typename... xs>
struct FlattenAsTypeList<TypeList<TypeList<xs...>>> : FlattenAsTypeList<TypeList<xs...>>
{ };


template <typename... xs>
using FlattenAsTypeListT = typename FlattenAsTypeList<xs...>::type;


#endif //ROCKY_BASE_TYPELISTFLATTEN_H

