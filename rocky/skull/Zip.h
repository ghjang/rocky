#ifndef ROCKY_SKULL_ZIP_H
#define ROCKY_SKULL_ZIP_H


#include "rocky/skull/ZipWith.h"


namespace Detail
{
    template <typename x, typename y>
    struct AsPairTypeList : type_is<TypeList<x, y>>
    { };

    template <typename x, typename y>
    struct AsPairTuple : type_is<std::tuple<x, y>>
    { };
} // namespace Detail


template <typename xs, typename ys>
struct Zip;

template <typename xs, typename ys>
using ZipT = typename Zip<xs, ys>::type;

template <typename... xs, typename... ys>
struct Zip<TypeList<xs...>, TypeList<ys...>> : ZipWith<Detail::AsPairTypeList, TypeList<xs...>, TypeList<ys...>>
{ };

template <typename... xs, typename... ys>
struct Zip<std::tuple<xs...>, std::tuple<ys...>> : ZipWith<Detail::AsPairTuple, std::tuple<xs...>, std::tuple<ys...>>
{ };


#endif //ROCKY_SKULL_ZIP_H

