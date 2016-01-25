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


/**
 * NOTE: Well, Range could be implemented by using the fold.
 *         But, I don't see any point to use the fold over the recursion,... at least for C++ TMP...
 *         It's more complicated. And even worse, I just guess that it has poorer compile-time performance.
 */
/*
template <typename T, T x, T y>
struct Range<std::integral_constant<T, x>, std::integral_constant<T, y>>
{
    static_assert(x <= y, "x should be equal or greater than y.");

private:
    template <typename lhs, typename rhs>
    struct AppendSummedIntegralConstant;

    template <T... lhs, T rhs>
    struct AppendSummedIntegralConstant<
                    TypeList<std::integral_constant<T, lhs>...>,
                    std::integral_constant<T, rhs>
            >
    {
        using next_int_t = HeadT<TypeList<std::integral_constant<T, lhs>...>>;
        using joined_t = TypeList<std::integral_constant<T, lhs>..., next_int_t>;
        using type = FlattenTypeListT<std::integral_constant<T, next_int_t() + 1>, TailT<joined_t>>;
    };

public:
    using type = TailT<
                    FoldLT<
                            AppendSummedIntegralConstant,
                            TypeList<std::integral_constant<T, x>>, // NOTE: init value for storing next int.
                            ReplicateT<y - x + 1, std::integral_constant<T, 1>>
                    >
                 >;
};
*/

template <int x, int y>
using MakeRangeT = RangeT<int_c_t<x>, int_c_t<y>>;

template <int x, int y>
using MakeRangeSequenceT = IntConstListToIntSeqT<MakeRangeT<x, y>>;


template <char x, char y>
using MakeCharRangeT = RangeT<std::integral_constant<char, x>, std::integral_constant<char, y>>;

template <char x, char y>
using MakeCharRangeSequenceT = IntConstListToIntSeqT<MakeCharRangeT<x, y>>;


template <typename T, T x, T y, T z>
struct Range<std::integral_constant<T, x>, std::integral_constant<T, y>, std::integral_constant<T, z>>
{
    static_assert(x < y, "x should be greater than y.");
    static_assert(y <= z, "y should be equal or greater than z.");

private:
    static constexpr T incrementValue_ = y - x;
    static constexpr T loopCount_ = (z - x) / incrementValue_;

    template <typename... xs>
    struct SteppedRangeImpl;

    template <T x1, T... i>
    struct SteppedRangeImpl<
                std::integral_constant<T, 0>,
                std::integral_constant<T, x1>,
                TypeList<std::integral_constant<T, i>...>
            >
            : type_is<TypeList<std::integral_constant<T, i>..., std::integral_constant<T, x1>>>
    { };

    template <T cnt, T x1, T... i>
    struct SteppedRangeImpl<
                std::integral_constant<T, cnt>,
                std::integral_constant<T, x1>,
                TypeList<std::integral_constant<T, i>...>
            >
            : SteppedRangeImpl<
                    std::integral_constant<T, cnt - 1>,
                    std::integral_constant<T, x1 + incrementValue_>,
                    TypeList<std::integral_constant<T, i>..., std::integral_constant<T, x1>>
              >
    { };

public:
    using type = typename SteppedRangeImpl<
                                std::integral_constant<T, loopCount_>,
                                std::integral_constant<T, x>,
                                TypeList<>
                            >::type;
};


template <int x, int y, int z>
using MakeSteppedRangeT = RangeT<int_c_t<x>, int_c_t<y>, int_c_t<z>>;

template <int x, int y, int z>
using MakeSteppedRangeSequenceT = IntConstListToIntSeqT<MakeSteppedRangeT<x, y, z>>;


template <char x, char y, char z>
using MakeSteppedCharRangeT = RangeT<
                                    std::integral_constant<char, x>,
                                    std::integral_constant<char, y>,
                                    std::integral_constant<char, z>
                                >;

template <char x, char y, char z>
using MakeSteppedCharRangeSequenceT = IntConstListToIntSeqT<MakeSteppedCharRangeT<x, y, z>>;


#endif //ROCKY_SKULL_RANGE_H

