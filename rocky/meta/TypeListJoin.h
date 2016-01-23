#ifndef ROCKY_TYPELISTFLATTEN_H
#define ROCKY_TYPELISTFLATTEN_H


#include "rocky/meta/TypeList.h"


template <typename... T>
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


template <typename... T>
using FlattenTypeListT = typename FlattenTypeList<T...>::type;


template <typename... T1, typename... T2>
constexpr auto operator + (TypeList<T1...>, TypeList<T2...>)
{
    return TypeList<T1..., T2...>{};
}


#endif //ROCKY_TYPELISTFLATTEN_H

