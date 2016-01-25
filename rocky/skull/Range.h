#ifndef ROCKY_SKULL_RANGE_H
#define ROCKY_SKULL_RANGE_H


#include "rocky/meta/IntegerSequenceUtility.h"


template <typename x, typename y, typename z = void>
struct Range;


template <typename x, typename y, typename z = void>
using RangeT = typename Range<x, y, z>::type;


template <typename T, T x, T y>
struct Range<std::integral_constant<T, x>, std::integral_constant<T, y>>
{
    static_assert(x <= y, "x should be equal or greater than y.");

private:
    template <typename... xs>
    struct RangeImpl;

    template <T y1, T... i>
    struct RangeImpl<
                std::integral_constant<T, y1>,
                std::integral_constant<T, y1>,
                TypeList<std::integral_constant<T, i>...>
            >
            : type_is<
                    TypeList<std::integral_constant<T, i>..., std::integral_constant<T, y1>>
              >
    { };

    template <T x1, T y1, T... i>
    struct RangeImpl<
                std::integral_constant<T, x1>,
                std::integral_constant<T, y1>,
                TypeList<std::integral_constant<T, i>...>
            >
            : RangeImpl<
                    std::integral_constant<T, x1 + 1>,
                    std::integral_constant<T, y1>,
                    TypeList<std::integral_constant<T, i>..., std::integral_constant<T, x1>>
              >
    { };


public:
    using type = typename RangeImpl<
                                std::integral_constant<T, x>,
                                std::integral_constant<T, y>,
                                TypeList<>
                            >::type;
};


template <int x, int y>
using MakeRangeT = RangeT<int_c_t<x>, int_c_t<y>>;


template <int x, int y>
using MakeRangeSequenceT = IntConstListToIntSeqT<MakeRangeT<x, y>>;


#endif //ROCKY_SKULL_RANGE_H

