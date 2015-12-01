#include "catch.hpp"

#include "rocky/meta/Fold.h"

#include "rocky/meta/IntegralConstantUtility.h"


TEST_CASE("fold right, integral constant sum", "[Fold]")
{
    using std::integral_constant;

    using sum_t = typename FoldRight<
                                IntegralConstantSum,
                                integral_constant<int, 0>,  // init
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >::type;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant subtract", "[Fold]")
{
    using std::integral_constant;

    using subtract_t = typename FoldRight<
                                    IntegralConstantSubtract,
                                    integral_constant<int, 0>,  // init
                                    integral_constant<int, 1>,
                                    integral_constant<int, 2>,
                                    integral_constant<int, 3>,
                                    integral_constant<int, 4>,
                                    integral_constant<int, 5>
                                >::type;
    static_assert(subtract_t() == 3, "(1 - (2 - (3 - (4 - (5 - 0))))) = 3");
}

TEST_CASE("fold right, integral constant in tuple sum", "[Fold]")
{
    using std::integral_constant;
    using std::tuple;

    using integral_tuple_t = tuple<
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >;

    using sum_t = typename FoldRight<
                                IntegralConstantSum,
                                integral_constant<int, 0>,  // init
                                integral_tuple_t
                            >::type;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant multiply", "[Fold]")
{
    using std::integral_constant;

    using mul_t = typename FoldRight<
                                IntegralConstantMultiply,
                                integral_constant<int, 1>,  // init
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >::type;
    static_assert(mul_t() == 120, "1 * (2 * (3 * (4 * (5 * 1)))) = 120");
}

TEST_CASE("fold left, integral constant sum", "[Fold]")
{
    using std::integral_constant;

    using sum_t = typename FoldLeft<
                                IntegralConstantSum,
                                integral_constant<int, 0>,  // init
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >::type;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant subtract", "[Fold]")
{
    using std::integral_constant;

    using subtract_t = typename FoldLeft<
                                    IntegralConstantSubtract,
                                    integral_constant<int, 0>,  // init
                                    integral_constant<int, 1>,
                                    integral_constant<int, 2>,
                                    integral_constant<int, 3>,
                                    integral_constant<int, 4>,
                                    integral_constant<int, 5>
                                >::type;
    static_assert(subtract_t() == -15, "(((((0 - 1) - 2) - 3) - 4) - 5) = -15");
}

TEST_CASE("fold left, integral constant in tuple sum", "[Fold]")
{
    using std::integral_constant;
    using std::tuple;

    using integral_tuple_t = tuple<
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >;

    using sum_t = typename FoldLeft<
                                IntegralConstantSum,
                                integral_constant<int, 0>,  // init
                                integral_tuple_t
                            >::type;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

TEST_CASE("fold left, integral constant multiply", "[Fold]")
{
    using std::integral_constant;

    using mul_t = typename FoldLeft<
                                IntegralConstantMultiply,
                                integral_constant<int, 1>,  // init
                                integral_constant<int, 1>,
                                integral_constant<int, 2>,
                                integral_constant<int, 3>,
                                integral_constant<int, 4>,
                                integral_constant<int, 5>
                            >::type;
    static_assert(mul_t() == 120, "(((((1 * 1) * 2) * 3) * 4) * 5) = 120");
}

