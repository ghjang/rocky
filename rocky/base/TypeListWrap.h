#ifndef ROCKY_BASE_TYPELISTWRAP_H
#define ROCKY_BASE_TYPELISTWRAP_H


#include "rocky/base/TypeList.h"


template <typename... xs>
struct WrapAsTypeList;

template <typename... T1, typename... T2>
struct WrapAsTypeList<TypeList<T1...>, TypeList<T2...>>
        : type_is<TypeList<TypeList<T1...>, TypeList<T2...>>>
{ };

template <typename... T1, typename... T2>
struct WrapAsTypeList<TypeList<T1...>, T2...>
        : type_is<TypeList<TypeList<T1...>, T2...>>
{ };

template <typename T1, typename... T2>
struct WrapAsTypeList<T1, TypeList<T2...>>
        : type_is<TypeList<T1, TypeList<T2...>>>
{ };


template <typename... xs>
using WrapAsTypeListT = typename WrapAsTypeList<xs...>::type;


template <typename... T1, typename... T2>
constexpr auto operator + (TypeList<T1...>, TypeList<T2...>)
{
    return TypeList<TypeList<T1...>, TypeList<T2...>>{};
}


#endif //ROCKY_BASE_TYPELISTWRAP_H

