#ifndef ROCKY_BASE_TYPECOMPOSITION_H
#define ROCKY_BASE_TYPECOMPOSITION_H


#include "rocky/skull/FoldR.h"
#include "rocky/skull/Last.h"
#include "rocky/skull/Init.h"


/**
 * The result is a composed metafunction class.
 *
 * You can think it as a some kind of metafunction class pipe-lining.
 *
 * @tparam f metafunction classes
 */
template <typename... f>
struct Compose
{
    static_assert(sizeof...(f) > 0, "no metafunction classes to compose.");

    template <typename... xs>
    struct Apply
            : FoldRWithTypeListUnpack<
                    Quote<::Apply>,
                    ApplyT<LastT<f...>, xs...>,
                    InitT<f...>
              >
    { };
};

template <typename... f>
struct Compose<TypeList<f...>> : Compose<f...>
{ };


/**
 * NegatePredicate itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam p predicate metafunction class
 */
template <typename p>
struct NegatePredicate
{
    template <typename T>
    struct Apply : std::integral_constant<bool, !ApplyT<p, T>::value>
    { };
};

/**
 * BindFirst itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam f metafunction class
 * @tparam xs type list to bind first
 */
template <typename f, typename... xs>
struct BindFirst
{
    template <typename... ys>
    struct Apply : ::Apply<f, xs..., ys...>
    { };
};

/**
 * BindLast itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam f metafunction class
 * @tparam xs type list to bind last
 */
template <typename f, typename... xs>
struct BindLast
{
    template <typename... ys>
    struct Apply : ::Apply<f, ys..., xs...>
    { };
};

/**
 * BindLastTemplate itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam f metafunction class
 * @tparam xs template list to bind last
 */
template <typename f, template <typename...> class... xs>
struct BindLastTemplate
{
    template <template <typename...> class... ys>
    struct Apply : ApplyTemplate<f, ys..., xs...>
    { };
};


#endif //ROCKY_BASE_TYPECOMPOSITION_H

