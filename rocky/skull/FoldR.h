#ifndef ROCKY_SKULL_FOLDR_H
#define ROCKY_SKULL_FOLDR_H


#include "rocky/base/TypeList.h"
#include "rocky/base/TypeUtility.h"
#include "rocky/base/HasMember.h"


// accumulation


/**
 * assumed that F is op:
 *  (t0 op (t1 op (t2 op ...(tn op init)...)
 *
 *  @tparam f (binary) metafunction class
 */
template <typename f, typename init, typename... xs>
struct FoldR;


template <typename f, typename init, typename... xs>
using FoldRT = typename FoldR<f, init, xs...>::type;


template <typename f, typename init>
struct FoldR<f, init> : type_is<init>
{ };

template <typename f, typename init, typename x, typename... xs>
struct FoldR<f, init, x, xs...> : Apply<f, x, FoldRT<f, init, xs...>>
{
    static_assert(HasTypeMember<Apply<f, x, init>>(), "applied metafunction class f should have 'type' member.");
};


/**
 * NOTE: An element type of the type list can be another type list itself.
 *       In that cases, the element type list will be un-packed un-expectedly.
 *       And it will result in (compile-time) errors.
 *
 *       If you need to handle a type list of type lists, use FoldRWithTypeListUnpack instead.
 */
/*
template <typename f, typename init, typename... xs>
struct FoldR<f, init, TypeList<xs...>> : FoldR<f, init, xs...>
{ };

template <typename f, typename init, typename... xs>
struct FoldR<f, init, std::tuple<xs...>> : FoldR<f, init, xs...>
{ };
 */


template <typename f, typename init, typename xs>
struct FoldRWithTypeListUnpack;

template <typename f, typename init, typename... xs>
struct FoldRWithTypeListUnpack<f, init, TypeList<xs...>> : FoldR<f, init, xs...>
{ };

template <typename f, typename init, typename... xs>
struct FoldRWithTypeListUnpack<f, init, std::tuple<xs...>> : FoldR<f, init, xs...>
{ };

template <typename f, typename init, typename xs>
using FoldRWithUnpackT = typename FoldRWithTypeListUnpack<f, init, xs>::type;


#endif //ROCKY_SKULL_FOLDR_H

