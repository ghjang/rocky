#ifndef ROCKY_BASE_TYPELISTUTILITY_H
#define ROCKY_BASE_TYPELISTUTILITY_H


#include "rocky/base/TypeList.h"


template <typename x>
struct IsTypeListContainer : std::false_type
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct IsTypeListContainer<TypeListContainer<xs...>> : std::true_type
{ };


template <typename xs>
struct EmptyTypeListContainerOf;

template <template <typename...> class TypeListContainer, typename... xs>
struct EmptyTypeListContainerOf<TypeListContainer<xs...>> : type_is<TypeListContainer<>>
{ };

template <typename xs>
using EmptyTypeListContainerOfT = typename EmptyTypeListContainerOf<xs>::type;


template <template <typename...> class TypeListContainer, typename x, typename y>
struct AsPairTypeListContainer : type_is<TypeListContainer<x, y>>
{ };

template <typename x, typename y>
struct AsPairTypeList : AsPairTypeListContainer<TypeList, x, y>
{ };

template <typename x, typename y>
struct AsPairTuple : AsPairTypeListContainer<std::tuple, x, y>
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


#endif //ROCKY_BASE_TYPELISTUTILITY_H

