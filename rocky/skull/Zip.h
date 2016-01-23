#ifndef ROCKY_SKULL_ZIP_H
#define ROCKY_SKULL_ZIP_H


#include "rocky/meta/TypeList.h"
#include "rocky/meta/TypeListFlatten.h"


namespace Detail
{
    template <typename xs, typename ys>
    struct ZipImpl;

    template <>
    struct ZipImpl<TypeList<>, TypeList<>> : type_is<TypeList<>>
    { };

    template <typename... xs>
    struct ZipImpl<TypeList<xs...>, TypeList<>> : type_is<TypeList<>>
    { };

    template <typename... ys>
    struct ZipImpl<TypeList<>, TypeList<ys...>> : type_is<TypeList<>>
    { };

    template <typename xs, typename ys>
    using ZipImplT = typename ZipImpl<xs, ys>::type;

    template <typename x, typename... xs, typename y, typename... ys>
    struct ZipImpl<TypeList<x, xs...>, TypeList<y, ys...>>
            : FlattenTypeList<std::pair<x, y>, ZipImplT<TypeList<xs...>, TypeList<ys...>>>
    { };
} // namespace Detail


template <typename xs, typename ys>
struct Zip;

template <typename... xs, typename... ys>
struct Zip<TypeList<xs...>, TypeList<ys...>>
        : Detail::ZipImpl<TypeList<xs...>, TypeList<ys...>>
{ };


template <typename xs, typename ys>
using ZipT = typename Zip<xs, ys>::type;


template <typename... xs, typename... ys>
struct Zip<std::tuple<xs...>, std::tuple<ys...>>
        : TypeListToTuple<ZipT<TypeList<xs...>, TypeList<ys...>>>
{ };


#endif //ROCKY_SKULL_ZIP_H

