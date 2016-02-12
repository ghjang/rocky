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


template <typename SourceTypeList, template <typename...> class TargetTypeListContainer>
struct ReplaceTypeListContainerType;

template <template <typename...> class S, typename... xs, template <typename...> class T>
struct ReplaceTypeListContainerType<S<xs...>, T> : type_is<T<xs...>>
{ };

template <typename xs>
using ToTuple = ReplaceTypeListContainerType<xs, std::tuple>;

template <typename xs>
using ToTupleT = typename ToTuple<xs>::type;

template <typename xs>
using ToTypeList = typename ReplaceTypeListContainerType<xs, TypeList>::type;

template <typename xs>
using ToTypeListT = typename ToTypeList<xs>::type;


#endif //ROCKY_BASE_TYPELIST_H

