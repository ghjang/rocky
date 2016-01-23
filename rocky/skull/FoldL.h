#ifndef ROCKY_SKULL_FOLDL_H
#define ROCKY_SKULL_FOLDL_H


#include "rocky/meta/TypeList.h"


// accumulation


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


#endif //ROCKY_SKULL_FOLDL_H

