#ifndef ROCKY_SKULL_ZIPWITH_H
#define ROCKY_SKULL_ZIPWITH_H


#include "rocky/base/TypeList.h"


namespace Detail
{
    template <template <typename, typename> class f, typename xs, typename ys, typename zs>
    struct ZipWithImpl;


    template <template <typename, typename> class f, typename... zs>
    struct ZipWithImpl<f, TypeList<>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <template <typename, typename> class f, typename... xs, typename... zs>
    struct ZipWithImpl<f, TypeList<xs...>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <template <typename, typename> class f, typename... ys, typename... zs>
    struct ZipWithImpl<f, TypeList<>, TypeList<ys...>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <template <typename, typename> class f, typename x, typename... xs, typename y, typename... ys, typename... zs>
    struct ZipWithImpl<f, TypeList<x, xs...>, TypeList<y, ys...>, TypeList<zs...>>
            : ZipWithImpl<f, TypeList<xs...>, TypeList<ys...>, TypeList<zs..., typename f<x, y>::type>>
    { };


    template <template <typename, typename> class f, typename xs, typename ys, typename zs>
    using ZipWithImplT = typename ZipWithImpl<f, xs, ys, zs>::type;


    template <template <typename, typename> class f, typename... zs>
    struct ZipWithImpl<f, std::tuple<>, std::tuple<>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <template <typename, typename> class f, typename... xs, typename... zs>
    struct ZipWithImpl<f, std::tuple<xs...>, std::tuple<>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <template <typename, typename> class f, typename... ys, typename... zs>
    struct ZipWithImpl<f, std::tuple<>, std::tuple<ys...>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <template <typename, typename> class f, typename x, typename... xs, typename y, typename... ys, typename... zs>
    struct ZipWithImpl<f, std::tuple<x, xs...>, std::tuple<y, ys...>, std::tuple<zs...>>
            : ZipWithImpl<f, std::tuple<xs...>, std::tuple<ys...>, std::tuple<zs..., typename f<x, y>::type>>
    { };
} // namespace Detail


template <template <typename, typename> class f, typename xs, typename ys>
struct ZipWith;

template <template <typename, typename> class f, typename... xs, typename... ys>
struct ZipWith<f, TypeList<xs...>, TypeList<ys...>>
        : Detail::ZipWithImpl<f, TypeList<xs...>, TypeList<ys...>, TypeList<>>
{ };


template <template <typename, typename> class f, typename xs, typename ys>
using ZipWithT = typename ZipWith<f, xs, ys>::type;


template <template <typename, typename> class f, typename... xs, typename... ys>
struct ZipWith<f, std::tuple<xs...>, std::tuple<ys...>>
        : Detail::ZipWithImpl<f, std::tuple<xs...>, std::tuple<ys...>, std::tuple<>>
{ };


#endif //ROCKY_SKULL_ZIPWITH_H

