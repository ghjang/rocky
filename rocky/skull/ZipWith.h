#ifndef ROCKY_SKULL_ZIPWITH_H
#define ROCKY_SKULL_ZIPWITH_H


#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeComposition.h"
#include "rocky/skull/Map.h"


namespace Detail
{
    template <typename f, typename xs, typename ys, typename zs>
    struct ZipWithImpl;

    template <typename f, typename... zs>
    struct ZipWithImpl<f, TypeList<>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename f, typename... xs, typename... zs>
    struct ZipWithImpl<f, TypeList<xs...>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename f, typename... ys, typename... zs>
    struct ZipWithImpl<f, TypeList<>, TypeList<ys...>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename f, typename x, typename... xs, typename y, typename... ys, typename... zs>
    struct ZipWithImpl<f, TypeList<x, xs...>, TypeList<y, ys...>, TypeList<zs...>>
            : ZipWithImpl<f, TypeList<xs...>, TypeList<ys...>, TypeList<zs..., ApplyT<f, x, y>>>
    { };
} // namespace Detail


/**
 * @tparam f (binary) metafunction class
 * @tparam xs first type list
 * @tparam ys second type list
 */
template <typename f, typename xs, typename ys>
struct ZipWith;

template <typename f, template <typename...> class TypeListContainer, typename... xs, typename... ys>
struct ZipWith<f, TypeListContainer<xs...>, TypeListContainer<ys...>>
        : ReplaceTypeListContainer<
                typename Detail::ZipWithImpl<f, TypeList<xs...>, TypeList<ys...>, TypeList<>>::type,
                TypeListContainer
          >
{ };


template <typename f, typename xs, typename ys>
using ZipWithT = typename ZipWith<f, xs, ys>::type;


#endif //ROCKY_SKULL_ZIPWITH_H

