#ifndef ROCKY_TYPELISTFLATTEN_H
#define ROCKY_TYPELISTFLATTEN_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct FlattenTypeList;

template <typename... T1, typename... T2>
struct FlattenTypeList<TypeList<T1...>, TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };

template <typename... T1, typename... T2>
struct FlattenTypeList<TypeList<T1...>, T2...> : type_is<TypeList<T1..., T2...>>
{ };

template <typename T1, typename... T2>
struct FlattenTypeList<T1, TypeList<T2...>> : type_is<TypeList<T1, T2...>>
{ };

template <typename... xs>
struct FlattenTypeList<TypeList<xs...>> : type_is<TypeList<xs...>>
{ };

template <typename... xs>
struct FlattenTypeList<TypeList<TypeList<xs...>>> : FlattenTypeList<TypeList<xs...>>
{ };

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2>
struct FlattenTypeList<T1..., TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };
 */

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2, typename... T3>
struct FlattenTypeList<T1..., TypeList<T2...>, T3...> : type_is<TypeList<T1..., T2..., T3...>>
{ };
 */


template <typename... xs>
using FlattenTypeListT = typename FlattenTypeList<xs...>::type;


#endif //ROCKY_TYPELISTFLATTEN_H

