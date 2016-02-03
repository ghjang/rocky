#include "../catch.hpp"

#include "rocky/skull/Max.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Max", "[skull]")
{
    static_assert(3 == Max<int_c_t<3>, int_c_t<3>>(), "");
    static_assert(3 == Max<int_c_t<2>, int_c_t<3>>(), "");
    static_assert(3 == Max<int_c_t<3>, int_c_t<2>>(), "");
}

