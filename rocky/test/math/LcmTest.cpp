#include "../catch.hpp"

#include "rocky/math/Lcm.h"


TEST_CASE("Lcm", "[math]")
{
    // NOTE: following are expected compile-time errors.
    //static_assert(1 == LCM<0, 0>());
    //static_assert(1 == LCM<1, 0>());
    //static_assert(1 == LCM<0, 1>());

    static_assert(1 == LCM<1, 1>());
    static_assert(3 == LCM<1, 3>());
    static_assert(15 == LCM<3, 5>());
    static_assert(50 == LCM<25, 10>());
}

