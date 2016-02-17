#ifndef ROCKY_BASE_TYPELIST_H
#define ROCKY_BASE_TYPELIST_H


#include <tuple>

#include "rocky/base/Identity.h"


template <typename... xs>
struct TypeList
{ };

template <typename... xs>
using TL = TypeList<xs...>;


template <typename... xs>
struct TypeListSize : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <typename... xs>
struct TypeListSize<TypeList<xs...>> : TypeListSize<xs...>
{ };


template <typename f>
struct FunctionParameterListSize;

template <typename r, typename... params>
struct FunctionParameterListSize<r (params...)> : std::integral_constant<std::size_t, sizeof...(params)>
{ };

template <typename r, typename... params>
struct FunctionParameterListSize<r (&) (params...)> : FunctionParameterListSize<r (params...)>
{ };

template <typename r, typename... params>
struct FunctionParameterListSize<r (*) (params...)> : FunctionParameterListSize<r (params...)>
{ };


template <typename x, typename y>
struct AsPairTypeList : type_is<TypeList<x, y>>
{ };

template <typename x, typename y>
struct AsPairTuple : type_is<std::tuple<x, y>>
{ };


template <typename SourceTypeList, template <typename...> class TargetTypeListContainer>
struct ReplaceTypeListContainerType;

template <template <typename...> class S, typename... xs, template <typename...> class T>
struct ReplaceTypeListContainerType<S<xs...>, T> : type_is<T<xs...>>
{ };


template <typename xs>
struct ToTuple : ReplaceTypeListContainerType<xs, std::tuple>
{ };

template <typename xs>
using ToTupleT = typename ToTuple<xs>::type;


template <typename xs>
struct ToTypeList : ReplaceTypeListContainerType<xs, TypeList>
{ };

template <typename xs>
using ToTypeListT = typename ToTypeList<xs>::type;


#endif //ROCKY_BASE_TYPELIST_H

