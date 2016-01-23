#ifndef ROCKY_TYPELIST_H
#define ROCKY_TYPELIST_H


#include "rocky/meta/Identity.h"


template <typename... xs>
struct TypeList
{ };


template <typename... xs>
struct TypeListSize : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <typename... xs>
struct TypeListSize<TypeList<xs...>> : TypeListSize<xs...>
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


template <typename... T>
using JoinTypeListT = typename JoinTypeList<T...>::type;


template <typename... T1, typename... T2>
constexpr auto operator + (TypeList<T1...>, TypeList<T2...>)
{
    return TypeList<T1..., T2...>{};
}


template <typename T>
struct TypeListToTuple;

template <typename... xs>
struct TypeListToTuple<TypeList<xs...>> : type_is<std::tuple<xs...>>
{ };


template <typename... xs>
using TypeListToTupleT = typename TypeListToTuple<xs...>::type;


#endif //ROCKY_TYPELIST_H

