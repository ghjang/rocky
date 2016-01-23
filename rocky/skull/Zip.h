#ifndef ROCKY_SKULL_ZIP_H
#define ROCKY_SKULL_ZIP_H


#include "rocky/meta/TypeList.h"


namespace Detail
{
    template <typename xs, typename ys, typename zs>
    struct ZipImpl;


    template <typename... zs>
    struct ZipImpl<TypeList<>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename... xs, typename... zs>
    struct ZipImpl<TypeList<xs...>, TypeList<>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename... ys, typename... zs>
    struct ZipImpl<TypeList<>, TypeList<ys...>, TypeList<zs...>> : type_is<TypeList<zs...>>
    { };

    template <typename x, typename... xs, typename y, typename... ys, typename... zs>
    struct ZipImpl<TypeList<x, xs...>, TypeList<y, ys...>, TypeList<zs...>>
            : ZipImpl<TypeList<xs...>, TypeList<ys...>, TypeList<zs..., TypeList<x, y>>>
    { };


    template <typename xs, typename ys, typename zs>
    using ZipImplT = typename ZipImpl<xs, ys, zs>::type;


    template <typename... zs>
    struct ZipImpl<std::tuple<>, std::tuple<>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <typename... xs, typename... zs>
    struct ZipImpl<std::tuple<xs...>, std::tuple<>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <typename... ys, typename... zs>
    struct ZipImpl<std::tuple<>, std::tuple<ys...>, std::tuple<zs...>> : type_is<std::tuple<zs...>>
    { };

    template <typename x, typename... xs, typename y, typename... ys, typename... zs>
    struct ZipImpl<std::tuple<x, xs...>, std::tuple<y, ys...>, std::tuple<zs...>>
            : ZipImpl<std::tuple<xs...>, std::tuple<ys...>, std::tuple<zs..., std::tuple<x, y>>>
    { };
} // namespace Detail


template <typename xs, typename ys>
struct Zip;

template <typename... xs, typename... ys>
struct Zip<TypeList<xs...>, TypeList<ys...>>
        : Detail::ZipImpl<TypeList<xs...>, TypeList<ys...>, TypeList<>>
{ };


template <typename xs, typename ys>
using ZipT = typename Zip<xs, ys>::type;


template <typename... xs, typename... ys>
struct Zip<std::tuple<xs...>, std::tuple<ys...>>
        : Detail::ZipImpl<std::tuple<xs...>, std::tuple<ys...>, std::tuple<>>
{ };


#endif //ROCKY_SKULL_ZIP_H

