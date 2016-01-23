#ifndef ROCKY_SKULL_FOLDR_H
#define ROCKY_SKULL_FOLDR_H


#include "rocky/meta/TypeList.h"


// accumulation


/**
 * assumed that F is op:
 *  (t0 op (t1 op (t2 op ...(tn op init)...)
 */
template <template <typename, typename> class f, typename init, typename... xs>
struct FoldR;


template <template <typename, typename> class f, typename init, typename... xs>
using FoldRT = typename FoldR<f, init, xs...>::type;


template <template <typename, typename> class f, typename init>
struct FoldR<f, init> : type_is<init>
{ };

template <template <typename, typename> class f, typename init, typename x, typename... xs>
struct FoldR<f, init, x, xs...> : f<x, FoldRT<f, init, xs...>>
{ };


template <template <typename, typename> class f, typename init, typename... xs>
struct FoldR<f, init, TypeList<xs...>> : FoldR<f, init, xs...>
{ };

template <template <typename, typename> class f, typename init, typename... xs>
struct FoldR<f, init, std::tuple<xs...>> : FoldR<f, init, xs...>
{ };


#endif //ROCKY_SKULL_FOLDR_H

