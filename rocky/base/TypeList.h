#ifndef ROCKY_BASE_TYPELIST_H
#define ROCKY_BASE_TYPELIST_H


#include <tuple>

#include "rocky/base/Identity.h"


template <typename... xs>
struct TypeList
{ };

template <typename... xs>
using TL = TypeList<xs...>;


namespace Detail
{
    /**
     * NOTE: for internal use only
     */
    struct __Guard__
    { };
} // namespace Detail


template <typename... xs>
struct TypeListSize : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct TypeListSize<TypeListContainer<xs...>> : TypeListSize<xs...>
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


template <template <typename...> class TypeListContainer, typename x, typename y>
struct AsPairTypeListContainer : type_is<TypeListContainer<x, y>>
{ };

template <typename x, typename y>
struct AsPairTypeList : AsPairTypeListContainer<TypeList, x, y>
{ };

template <typename x, typename y>
struct AsPairTuple : AsPairTypeListContainer<std::tuple, x, y>
{ };


template <typename SourceTypeList, template <typename...> class TargetTypeListContainer>
struct ReplaceTypeListContainer;

template <template <typename...> class S, typename... xs>
struct ReplaceTypeListContainer<S<xs...>, S> : type_is<S<xs...>>
{ };

template <template <typename...> class S, typename... xs, template <typename...> class T>
struct ReplaceTypeListContainer<S<xs...>, T> : type_is<T<xs...>>
{ };


template <typename xs>
struct ToTuple : ReplaceTypeListContainer<xs, std::tuple>
{ };

template <typename xs>
using ToTupleT = typename ToTuple<xs>::type;


template <typename xs>
struct ToTypeList : ReplaceTypeListContainer<xs, TypeList>
{ };

template <typename xs>
using ToTypeListT = typename ToTypeList<xs>::type;


#endif //ROCKY_BASE_TYPELIST_H

