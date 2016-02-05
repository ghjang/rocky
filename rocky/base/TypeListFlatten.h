#ifndef ROCKY_BASE_TYPELISTFLATTEN_H
#define ROCKY_BASE_TYPELISTFLATTEN_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct FlattenAsTypeList;

template <typename... T1, typename... T2>
struct FlattenAsTypeList<TypeList<T1...>, TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };

template <typename... T1, typename... T2>
struct FlattenAsTypeList<TypeList<T1...>, T2...> : type_is<TypeList<T1..., T2...>>
{ };

template <typename T1, typename... T2>
struct FlattenAsTypeList<T1, TypeList<T2...>> : type_is<TypeList<T1, T2...>>
{ };

template <typename... xs>
struct FlattenAsTypeList<TypeList<xs...>> : type_is<TypeList<xs...>>
{ };

template <typename... xs>
struct FlattenAsTypeList<TypeList<TypeList<xs...>>> : FlattenAsTypeList<TypeList<xs...>>
{ };

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2>
struct FlattenAsTypeList<T1..., TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };
 */

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2, typename... T3>
struct FlattenAsTypeList<T1..., TypeList<T2...>, T3...> : type_is<TypeList<T1..., T2..., T3...>>
{ };
 */


template <typename... xs>
using FlattenAsTypeListT = typename FlattenAsTypeList<xs...>::type;


#endif //ROCKY_BASE_TYPELISTFLATTEN_H

