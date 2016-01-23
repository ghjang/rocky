#ifndef ROCKY_SKULL_FOLDR_H
#define ROCKY_SKULL_FOLDR_H


#include "rocky/meta/TypeList.h"


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


#endif //ROCKY_SKULL_FOLDR_H

