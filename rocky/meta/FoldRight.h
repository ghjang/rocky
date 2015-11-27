#ifndef ROCKY_FOLDRIGHT_H
#define ROCKY_FOLDRIGHT_H


// accumulation


/**
 * assumed that F is op:
 *  t0 op (t1 op (t2 op ...(tn op init)...)
 */
template <template <typename, typename> class F, typename init, typename... list>
struct FoldRight;

template <template <typename, typename> class F, typename init>
struct FoldRight<F, init>
{
    using type = init;
};

template <template <typename, typename> class F, typename init, typename head, typename... tail>
struct FoldRight<F, init, head, tail...>
{
    using type = typename F<head, typename FoldRight<F, init, tail...>::type>::type;
};


#endif //ROCKY_FOLDRIGHT_H

