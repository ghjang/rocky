#ifndef ROCKY_TYPELISTJOIN_H
#define ROCKY_TYPELISTJOIN_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct JoinTypeList;

template <typename... T1, typename... T2>
struct JoinTypeList<TypeList<T1...>, TypeList<T2...>>
        : type_is<TypeList<TypeList<T1...>, TypeList<T2...>>>
{ };

template <typename... T1, typename... T2>
struct JoinTypeList<TypeList<T1...>, T2...>
        : type_is<TypeList<TypeList<T1...>, T2...>>
{ };

template <typename T1, typename... T2>
struct JoinTypeList<T1, TypeList<T2...>>
        : type_is<TypeList<T1, TypeList<T2...>>>
{ };


template <typename... xs>
using JoinTypeListT = typename JoinTypeList<xs...>::type;


template <typename... T1, typename... T2>
constexpr auto operator + (TypeList<T1...>, TypeList<T2...>)
{
    return TypeList<TypeList<T1...>, TypeList<T2...>>{};
}


#endif //ROCKY_TYPELISTJOIN_H

