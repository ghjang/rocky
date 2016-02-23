#ifndef ROCKY_SKULL_FOLDR_H
#define ROCKY_SKULL_FOLDR_H


#include "rocky/base/TypeList.h"
#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeComposition.h"
#include "rocky/base/HasMember.h"


// accumulation


namespace Detail
{
    template <typename f, typename init, typename... xs>
    struct FoldRImpl;

    template <typename f, typename init, typename... xs>
    using FoldRImplT = typename FoldRImpl<f, init, xs...>::type;

    template <typename f, typename init>
    struct FoldRImpl<f, init> : type_is<init>
    { };

    template <typename f, typename init, typename x, typename... xs>
    struct FoldRImpl<f, init, x, xs...> : Apply<f, x, FoldRImplT<f, init, xs...>>
    {
        static_assert(HasTypeMember<Apply<f, x, init>>(), "applied metafunction class f should have 'type' member.");
    };
}


/**
 * assumed that F is op:
 *  (t0 op (t1 op (t2 op ...(tn op init)...)
 *
 *  @tparam f (binary) metafunction class
 */
template <typename f, typename init, typename... xs>
struct FoldR : Detail::FoldRImpl<f, init, xs...>
{ };

template <typename f, typename init, template <typename...> class TypeListContainer, typename... xs>
struct FoldR<f, init, TypeListContainer<xs...>> : FoldR<f, init, xs...>
{ };


template <typename f, typename init, template <typename...> class mf>
struct FoldR<f, init, Quote<mf>> : Detail::FoldRImpl<f, init, Quote<mf>>
{ };


template <typename... f>
struct Compose;

template <typename p>
struct NegatePredicate;

template <typename f, typename... xs>
struct BindFirst;

template <typename f, typename... xs>
struct BindLast;


template <typename f, typename init, typename... mfc>
struct FoldR<f, init, Compose<mfc...>> : Detail::FoldRImpl<f, init, Compose<mfc...>>
{ };

template <typename f, typename init, typename pmf>
struct FoldR<f, init, NegatePredicate<pmf>> : Detail::FoldRImpl<f, init, NegatePredicate<pmf>>
{ };

template <typename f, typename init, typename... xs>
struct FoldR<f, init, BindFirst<xs...>> : Detail::FoldRImpl<f, init, BindFirst<xs...>>
{ };

template <typename f, typename init, typename... xs>
struct FoldR<f, init, BindLast<xs...>> : Detail::FoldRImpl<f, init, BindLast<xs...>>
{ };


template <typename f, typename init, typename... xs>
using FoldRT = typename FoldR<f, init, xs...>::type;


#endif //ROCKY_SKULL_FOLDR_H

