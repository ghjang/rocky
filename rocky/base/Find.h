#ifndef ROCKY_FIND_H
#define ROCKY_FIND_H


#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/FindIf.h"
#include "rocky/skull/Reverse.h"


/**
 * THINK: Is it possible to generalize this kind of currying?
 */
template <typename T>
struct IsSame
{
    template <typename x>
    struct Convert : std::is_same<x, T>
    { };
};


template <typename T, typename... xs>
struct Find : FindIf<IsSame<T>::template Convert, xs...>
{ };


template <typename T, typename... xs>
struct Find<T, TypeList<xs...>> : Find<T, xs...>
{ };

template <typename T, typename... xs>
struct Find<T, std::tuple<xs...>> : Find<T, xs...>
{ };


template <typename T, typename... xs>
struct ReverseFind : ReverseFindIf<IsSame<T>::template Convert, xs...>
{ };


template <typename T, typename... xs>
struct ReverseFind<T, TypeList<xs...>> : ReverseFind<T, xs...>
{ };

template <typename T, typename... xs>
struct ReverseFind<T, std::tuple<xs...>> : ReverseFind<T, xs...>
{ };


#endif //ROCKY_FIND_H

