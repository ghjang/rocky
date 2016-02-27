#ifndef ROCKY_BASE_FUNCTIONUTILITY_H
#define ROCKY_BASE_FUNCTIONUTILITY_H


#include <type_traits>


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


#endif //ROCKY_BASE_FUNCTIONUTILITY_H

