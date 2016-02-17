#ifndef ROCKY_SKULL_ZIP_H
#define ROCKY_SKULL_ZIP_H


#include "rocky/skull/ZipWith.h"


template <typename xs, typename ys>
struct Zip;

template <typename... xs, typename... ys>
struct Zip<TypeList<xs...>, TypeList<ys...>>
        : ZipWith<
                Quote<AsPairTypeList>,
                TypeList<xs...>,
                TypeList<ys...>
          >
{ };

template <typename... xs, typename... ys>
struct Zip<std::tuple<xs...>, std::tuple<ys...>>
        : ZipWith<
                Quote<AsPairTuple>,
                std::tuple<xs...>,
                std::tuple<ys...>
          >
{ };


template <typename xs, typename ys>
using ZipT = typename Zip<xs, ys>::type;


#endif //ROCKY_SKULL_ZIP_H

