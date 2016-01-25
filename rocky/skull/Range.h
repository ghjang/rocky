#ifndef ROCKY_SKULL_RANGE_H
#define ROCKY_SKULL_RANGE_H


#include "rocky/meta/IntegerSequenceUtility.h"


template <typename x, typename y, typename z = void>
struct Range;


template <typename x, typename y, typename z = void>
using RangeT = typename Range<x, y, z>::type;


template <int x, int y>
struct Range<int_c_t<x>, int_c_t<y>>
{
    static_assert(x <= y, "x should be equal or greater than y.");

private:
    template <typename... T>
    struct RangeImpl;

    template <int y1, int... i>
    struct RangeImpl<int_c_t<y1>, int_c_t<y1>, TypeList<int_c_t<i>...>>
            : type_is<
                    TypeList<int_c_t<i>..., int_c_t<y1>>
              >
    { };

    template <int x1, int y1, int... i>
    struct RangeImpl<int_c_t<x1>, int_c_t<y1>, TypeList<int_c_t<i>...>>
            : RangeImpl<
                    int_c_t<x1 + 1>,
                    int_c_t<y1>,
                    TypeList<int_c_t<i>..., int_c_t<x1>>
              >
    { };


public:
    using type = typename RangeImpl<int_c_t<x>, int_c_t<y>, TypeList<>>::type;
};


template <int x, int y>
using MakeRangeT = RangeT<int_c_t<x>, int_c_t<y>>;


template <int x, int y>
using MakeRangeSequenceT = IntConstListToIntSeqT<MakeRangeT<x, y>>;


#endif //ROCKY_SKULL_RANGE_H

