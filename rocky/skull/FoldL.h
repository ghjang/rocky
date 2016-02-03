#ifndef ROCKY_SKULL_FOLDL_H
#define ROCKY_SKULL_FOLDL_H


#include "rocky/base/TypeList.h"
#include "rocky/base/HasMember.h"


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
{
    static_assert(HasTypeMember<f<init, x>>(), "f should have 'type' member.");
};


template <template <typename, typename> class f, typename init, typename... xs>
using FoldLT = typename FoldL<f, init, xs...>::type;


/**
 * NOTE: The element type of the type list can be another type list itself.
 *       In that cases, the element type list will be un-packed un-expectedly.
 *       And it will result in (compile-time) errors.
 *
 *       If you need to handle a type list of type lists, use FoldLWithTypeListUnpack instead.
 */
/*
template <template <typename, typename> class f, typename init, typename... xs>
struct FoldL<f, init, TypeList<xs...>> : FoldL<f, init, xs...>
{ };

template <template <typename, typename> class f, typename init, typename... xs>
struct FoldL<f, init, std::tuple<xs...>> : FoldL<f, init, xs...>
{ };
 */


template <template <typename, typename> class f, typename init, typename xs>
struct FoldLWithTypeListUnpack;

template <template <typename, typename> class f, typename init, typename... xs>
struct FoldLWithTypeListUnpack<f, init, TypeList<xs...>> : FoldL<f, init, xs...>
{ };

template <template <typename, typename> class f, typename init, typename... xs>
struct FoldLWithTypeListUnpack<f, init, std::tuple<xs...>> : FoldL<f, init, xs...>
{ };

template <template <typename, typename> class f, typename init, typename xs>
using FoldLWithUnpackT = typename FoldLWithTypeListUnpack<f, init, xs>::type;


#endif //ROCKY_SKULL_FOLDL_H

