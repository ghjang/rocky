#ifndef ROCKY_BASE_TYPEAT_H
#define ROCKY_BASE_TYPEAT_H


#include "rocky/skull/Head.h"
#include "rocky/skull/Drop.h"


template <std::size_t i, typename... xs>
struct TypeAt
{
    static_assert(sizeof...(xs) > 0, "xs should have at least one parameter.");
    static_assert(i < sizeof...(xs), "i should have a valid index value.");
    using type = HeadT<DropT<i, xs...>>;
};

template <std::size_t i, typename... xs>
using TypeAtT = typename TypeAt<i, xs...>::type;


template <std::size_t i, typename... xs>
struct TypeAt<i, TypeList<xs...>> : TypeAt<i, xs...>
{ };

template <std::size_t i, typename... xs>
struct TypeAt<i, std::tuple<xs...>> : TypeAt<i, xs...>
{ };


template <std::size_t i, typename f>
struct FunctionParameterTypeAt;

template <std::size_t i, typename r, typename... params>
struct FunctionParameterTypeAt<i, r (params...)>
{
    static_assert(sizeof...(params) > 0, "params should have at least one parameter.");
    static_assert(i < sizeof...(params), "i should have a valid index value.");
    using type = HeadT<DropT<i, params...>>;
};

template <std::size_t i, typename r, typename... params>
struct FunctionParameterTypeAt<i, r (&) (params...)> : FunctionParameterTypeAt<i, r (params...)>
{ };

template <std::size_t i, typename r, typename... params>
struct FunctionParameterTypeAt<i, r (*) (params...)> : FunctionParameterTypeAt<i, r (params...)>
{ };


template <std::size_t i, typename f>
using FunctionParameterTypeAtT = typename FunctionParameterTypeAt<i, f>::type;


#endif //ROCKY_BASE_TYPEAT_H

