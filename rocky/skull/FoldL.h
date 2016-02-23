#ifndef ROCKY_SKULL_FOLDL_H
#define ROCKY_SKULL_FOLDL_H


#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeComposition.h"


// accumulation


namespace Detail
{
    template <typename f, typename init, typename... xs>
    struct FoldLImpl;

    template <typename f, typename last>
    struct FoldLImpl<f, last> : type_is<last>
    { };

    template <typename f, typename init, typename x, typename... xs>
    struct FoldLImpl<f, init, x, xs...> : FoldLImpl<f, ApplyT<f, init, x>, xs...>
    {
        static_assert(
                HasTypeMember<Apply<f, init, x>>(),
                "applied binary metafunction class f should have 'type' member."
        );
    };
} // namespace Detail


/**
 * assumed that F is op:
 *  (...(init op t0) op t1) op t2)... op tn)
 *
 *  @tparam f (binary) metafunction class
 */
template <typename f, typename init, typename... xs>
struct FoldL : Detail::FoldLImpl<f, init, xs...>
{ };

/**
 * NOTE: You need to do some proper workarounds if you don't want to un-pack the type list parameters.
 *       Refer to skull Concat metafunction implementation for an idea.
 */
template <typename f, typename init, template <typename...> class TypeListContainer, typename... xs>
struct FoldL<f, init, TypeListContainer<xs...>> : FoldL<f, init, xs...>
{ };

/**
 * NOTE: for zipped type lists of which length is 1.
 */
template <typename f, typename init, template <typename...> class TypeListContainer, typename... xs>
struct FoldL<f, init, TypeListContainer<TypeListContainer<xs...>>>
        : Detail::FoldLImpl<f, init, TypeListContainer<xs...>>
{ };


template <typename f, typename init, template <typename...> class mf>
struct FoldL<f, init, Quote<mf>> : Detail::FoldLImpl<f, init, Quote<mf>>
{ };


template <typename f, typename init, typename... mfc>
struct FoldL<f, init, Compose<mfc...>> : Detail::FoldLImpl<f, init, Compose<mfc...>>
{ };

template <typename f, typename init, typename pmf>
struct FoldL<f, init, NegatePredicate<pmf>> : Detail::FoldLImpl<f, init, NegatePredicate<pmf>>
{ };

template <typename f, typename init, typename... xs>
struct FoldL<f, init, BindFirst<xs...>> : Detail::FoldLImpl<f, init, BindFirst<xs...>>
{ };

template <typename f, typename init, typename... xs>
struct FoldL<f, init, BindLast<xs...>> : Detail::FoldLImpl<f, init, BindLast<xs...>>
{ };


template <typename f, typename init, typename... xs>
using FoldLT = typename FoldL<f, init, xs...>::type;


#endif //ROCKY_SKULL_FOLDL_H

