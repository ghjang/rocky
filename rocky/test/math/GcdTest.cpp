#include "../catch.hpp"

#include "rocky/math/Gcd.h"


TEST_CASE("Gcd", "[math]")
{
    static_assert(0 == GCD<0, 0>(), "");
    static_assert(0 == GCD<0, 1>(), "");
    static_assert(0 == GCD<1, 0>(), "");

    static_assert(1 == GCD<1, 1>(), "");
    static_assert(1 == GCD<1, 2>(), "");
    static_assert(1 == GCD<1, 3>(), "");
    static_assert(2 == GCD<2, 4>(), "");
    static_assert(2 == GCD<10, 6>(), "");
    static_assert(12 == GCD<12, 12>(), "");
}

