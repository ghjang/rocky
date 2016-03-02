#ifndef ROCKY_BASE_FUNCTIONUTILITY_H
#define ROCKY_BASE_FUNCTIONUTILITY_H


#include <type_traits>

#include "rocky/base/VoidT.h"
#include "rocky/base/TypeList.h"


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


template <typename f, typename... xs>
using test_function_call_t = decltype(std::declval<f>()(std::declval<xs>()...));

template <typename f, typename xs, typename = void>
struct IsCallableWith : std::false_type
{ };

template <typename f, typename... xs>
struct IsCallableWith<f, TypeList<xs...>, void_t<test_function_call_t<f, xs...>>> : std::true_type
{ };


#endif //ROCKY_BASE_FUNCTIONUTILITY_H

