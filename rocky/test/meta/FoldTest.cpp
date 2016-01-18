#include "../catch.hpp"

#include "rocky/meta/Fold.h"

#include "rocky/meta/IntegralConstantUtility.h"

#include <numeric>


TEST_CASE("runtime fold, std::accumulate", "[Fold]")
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    auto sum = std::accumulate(
                       v.begin(), v.end(),
                       0, // init
                       [](int lhs, int rhs) { return lhs + rhs; }
                );
    REQUIRE(15 == sum);
}

TEST_CASE("fold right, integral constant sum", "[Fold]")
{
    using sum_t = typename FoldRight<
                                IntegralConstantSum,
                                int_c_t<0>,  // init
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >::type;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant subtract", "[Fold]")
{
    using subtract_t = typename FoldRight<
                                    IntegralConstantSubtract,
                                    int_c_t<0>,  // init
                                    int_c_t<1>,
                                    int_c_t<2>,
                                    int_c_t<3>,
                                    int_c_t<4>,
                                    int_c_t<5>
                                >::type;
    static_assert(subtract_t() == 3, "(1 - (2 - (3 - (4 - (5 - 0))))) = 3");
}

TEST_CASE("fold right, integral constant in tuple sum", "[Fold]")
{
    using std::tuple;

    using integral_tuple_t = tuple<
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >;

    using sum_t = typename FoldRight<
                                IntegralConstantSum,
                                int_c_t<0>,  // init
                                integral_tuple_t
                            >::type;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant multiply", "[Fold]")
{
    using mul_t = typename FoldRight<
                                IntegralConstantMultiply,
                                int_c_t<1>,  // init
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >::type;
    static_assert(mul_t() == 120, "1 * (2 * (3 * (4 * (5 * 1)))) = 120");
}

TEST_CASE("fold left, integral constant sum", "[Fold]")
{
    using sum_t = typename FoldLeft<
                                IntegralConstantSum,
                                int_c_t<0>,  // init
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >::type;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant subtract", "[Fold]")
{
    using subtract_t = typename FoldLeft<
                                    IntegralConstantSubtract,
                                    int_c_t<0>,  // init
                                    int_c_t<1>,
                                    int_c_t<2>,
                                    int_c_t<3>,
                                    int_c_t<4>,
                                    int_c_t<5>
                                >::type;
    static_assert(subtract_t() == -15, "(((((0 - 1) - 2) - 3) - 4) - 5) = -15");
}

TEST_CASE("fold left, integral constant in tuple sum", "[Fold]")
{
    using std::tuple;

    using integral_tuple_t = tuple<
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >;

    using sum_t = typename FoldLeft<
                                IntegralConstantSum,
                                int_c_t<0>,  // init
                                integral_tuple_t
                            >::type;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant multiply", "[Fold]")
{
    using mul_t = typename FoldLeft<
                                IntegralConstantMultiply,
                                int_c_t<1>,  // init
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                            >::type;
    static_assert(mul_t() == 120, "(((((1 * 1) * 2) * 3) * 4) * 5) = 120");
}
