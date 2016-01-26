#ifndef ROCKY_TYPEAT_H
#define ROCKY_TYPEAT_H


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


#endif //ROCKY_TYPEAT_H

