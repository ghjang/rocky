#include "../catch.hpp"

#include "rocky/wolca/IntegerLength.h"


TEST_CASE("IntegerLength", "[wolca]")
{
    constexpr auto len = IntegerLength(1234567890);
    REQUIRE(len == 10);

    constexpr auto len1 = IntegerLength(0);
    REQUIRE(len1 == 1);

    constexpr auto len2 = IntegerLength(-1024);
    REQUIRE(len2 == 4);
}

