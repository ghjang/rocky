#ifndef ROCKY_BASE_TYPECOMPOSITION_H
#define ROCKY_BASE_TYPECOMPOSITION_H


#include "rocky/skull/FoldR.h"
#include "rocky/skull/Last.h"
#include "rocky/skull/Init.h"


/**
 * The result is a composed metafunction class.
 * You can think it as a some kind of metafunction pipe-lining.
 *
 * @tparam f metafunction classes
 */
template <typename... f>
struct Compose
{
private:
    template <typename lhs, typename rhs>
    struct ComposeImpl : ApplyT<lhs, rhs>
    { };

public:
    template <typename... xs>
    struct Apply
            : FoldRWithTypeListUnpack<
                    Quote<ComposeImpl>,
                    typename ApplyT<LastT<f...>, xs...>::type,
                    InitT<f...>
              >
    { };
};


/**
 * NegatePredicate itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam Predicate metafunction class
 */
template <typename Predicate>
struct NegatePredicate
{
    template <typename T>
    struct Apply : std::integral_constant<bool, !ApplyT<Predicate, T>::value>
    { };
};

/**
 * Bind1st is itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam BinaryF metafunction class
 */
template <typename BinaryF, typename T>
struct Bind1st
{
    template <typename V>
    struct Apply : ApplyT<BinaryF, T, V>
    { };
};

/**
 * Bind2nd is itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam BinaryF metafunction class
 */
template <typename BinaryF, typename T>
struct Bind2nd
{
    template <typename V>
    struct Apply : ApplyT<BinaryF, V, T>
    { };
};


#endif //ROCKY_BASE_TYPECOMPOSITION_H

