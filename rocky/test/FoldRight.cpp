#include "catch.hpp"

#include "rocky/meta/FoldRight.h"

#include "rocky/meta/IntegralConstantUtility.h"


TEST_CASE("integral constant sum", "[FoldRight]")
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

TEST_CASE("integral constant multiply", "[FoldRight]")
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

