#ifndef ROCKY_SKULL_FOLDL_H
#define ROCKY_SKULL_FOLDL_H


#include "rocky/meta/TypeList.h"


// accumulation


/**
 * assumed that F is op:
 *  (...(init op t0) op t1) op t2)... op tn)
 */
template <template <typename, typename> class f, typename init, typename... xs>
struct FoldL;

template <template <typename, typename> class f, typename last>
struct FoldL<f, last> : type_is<last>
{ };

template <template <typename, typename> class f, typename init, typename x, typename... xs>
struct FoldL<f, init, x, xs...> : FoldL<f, typename f<init, x>::type, xs...>
{ };


template <template <typename, typename> class f, typename init, typename... xs>
using FoldLT = typename FoldL<f, init, xs...>::type;


template <template <typename, typename> class f, typename init, typename... xs>
struct FoldL<f, init, TypeList<xs...>> : FoldL<f, init, xs...>
{ };

template <template <typename, typename> class f, typename init, typename... xs>
struct FoldL<f, init, std::tuple<xs...>> : FoldL<f, init, xs...>
{ };


#endif //ROCKY_SKULL_FOLDL_H

