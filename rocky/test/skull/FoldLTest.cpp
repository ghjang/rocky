#include "../catch.hpp"

#include "rocky/skull/FoldL.h"

#include "rocky/base/IntegralConstantUtility.h"

#include <numeric>


TEST_CASE("runtime fold, std::accumulate", "[FoldL]")
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    auto sum = std::accumulate(
                       v.begin(), v.end(),
                       0, // init
                       [](int lhs, int rhs) { return lhs + rhs; }
                );
    REQUIRE(15 == sum);
}

TEST_CASE("fold left, integral constant sum", "[FoldL]")
{
    using sum_t = FoldLT<
                        Quote<Plus>,
                        int_c_t<0>,  // init
                        int_c_t<1>,
                        int_c_t<2>,
                        int_c_t<3>,
                        int_c_t<4>,
                        int_c_t<5>
                  >;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant subtract", "[FoldL]")
{
    using subtract_t = FoldLT<
                            Quote<Minus>,
                            int_c_t<0>,  // init
                            int_c_t<1>,
                            int_c_t<2>,
                            int_c_t<3>,
                            int_c_t<4>,
                            int_c_t<5>
                       >;
    static_assert(subtract_t() == -15, "(((((0 - 1) - 2) - 3) - 4) - 5) = -15");
}

TEST_CASE("fold left, integral constant in tuple sum", "[FoldL]")
{
    using std::tuple;

    using integral_tuple_t = tuple<
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >;

    using sum_t = FoldLT<
                        Quote<Plus>,
                        int_c_t<0>,  // init
                        integral_tuple_t
                  >;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant multiply", "[FoldL]")
{
    using mul_t = FoldLT<
                        Quote<Multiply>,
                        int_c_t<1>,  // init
                        int_c_t<1>,
                        int_c_t<2>,
                        int_c_t<3>,
                        int_c_t<4>,
                        int_c_t<5>
                  >;
    static_assert(mul_t() == 120, "(((((1 * 1) * 2) * 3) * 4) * 5) = 120");
}

