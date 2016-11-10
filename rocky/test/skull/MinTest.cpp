#include "../catch.hpp"

#include "rocky/skull/Min.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Min", "[skull]")
{
    static_assert(2 == Min<int_c_t<2>, int_c_t<2>>());
    static_assert(2 == Min<int_c_t<2>, int_c_t<3>>());
    static_assert(2 == Min<int_c_t<3>, int_c_t<2>>());
}

