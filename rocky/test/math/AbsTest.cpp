#include "../catch.hpp"

#include "rocky/math/Abs.h"


TEST_CASE("Abs", "[Abs]")
{
    static_assert(Abs(10) == 10);
    static_assert(Abs(-10) == 10);

    uint ui = 10;
    REQUIRE(Abs(ui) == 10);
}

