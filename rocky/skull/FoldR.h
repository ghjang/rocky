#ifndef ROCKY_FOLD_H
#define ROCKY_FOLD_H


#include <tuple>

#include "rocky/meta/Identity.h"


// accumulation


/**
 * assumed that F is op:
 *  (t0 op (t1 op (t2 op ...(tn op init)...)
 */
template <template <typename, typename> class F, typename init, typename... list>
struct FoldRight;

template <template <typename, typename> class F, typename init>
struct FoldRight<F, init> : type_is<init>
{ };

template <template <typename, typename> class F, typename init, typename head, typename... tail>
struct FoldRight<F, init, head, tail...>
{
    using type = typename F<head, typename FoldRight<F, init, tail...>::type>::type;
};

template <template <typename, typename> class F, typename init, typename... list>
struct FoldRight<F, init, std::tuple<list...>>
        : FoldRight<F, init, list...>
{ };


/**
 * assumed that F is op:
 *  (...(init op t0) op t1) op t2)... op tn)
 */
template <template <typename, typename> class F, typename init, typename... list>
struct FoldLeft;

template <template <typename, typename> class F, typename last>
struct FoldLeft<F, last> : type_is<last>
{ };

template <template <typename, typename> class F, typename init, typename head, typename... tail>
struct FoldLeft<F, init, head, tail...>
        : FoldLeft<F, typename F<init, head>::type, tail...>
{ };

template <template <typename, typename> class F, typename init, typename... list>
struct FoldLeft<F, init, std::tuple<list...>>
        : FoldLeft<F, init, list...>
{ };


#endif //ROCKY_FOLD_H

