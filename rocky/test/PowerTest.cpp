#include "catch.hpp"

#include "rocky/math/Power.h"


TEST_CASE("power", "[Power]")
{
    static_assert(Power(10, 0) == 1, "10^0 = 1");
    static_assert(Power(10, 2) == 100, "10^2 = 100");
    static_assert(Power(2, 10) == 1024, "2^10 = 1024");
}

