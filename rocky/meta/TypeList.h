#ifndef ROCKY_TYPELIST_H
#define ROCKY_TYPELIST_H


#include "rocky/meta/Identity.h"


template <typename... T>
struct TypeList
{ };


template <typename... T>
struct JoinTypeList;

template <typename... T1, typename... T2>
struct JoinTypeList<TypeList<T1...>, TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };

template <typename... T1, typename... T2>
struct JoinTypeList<TypeList<T1...>, T2...> : type_is<TypeList<T1..., T2...>>
{ };

template <typename T1, typename... T2>
struct JoinTypeList<T1, TypeList<T2...>> : type_is<TypeList<T1, T2...>>
{ };

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2>
struct JoinTypeList<T1..., TypeList<T2...>> : type_is<TypeList<T1..., T2...>>
{ };
 */

/**
 * following is not a valid pattern matching.
 */
/*
template <typename... T1, typename... T2, typename... T3>
struct JoinTypeList<T1..., TypeList<T2...>, T3...> : type_is<TypeList<T1..., T2..., T3...>>
{ };
 */


template <typename... T1, typename... T2>
constexpr auto operator + (TypeList<T1...>, TypeList<T2...>)
{
    return TypeList<T1..., T2...>{};
}


#endif //ROCKY_TYPELIST_H

