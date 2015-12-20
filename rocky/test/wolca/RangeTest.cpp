#include "../catch.hpp"

#include "rocky/wolca/Range.h"


TEST_CASE("Range function", "[wolca]")
{
    {
        constexpr auto cr = Range<10>(); // compile-time
        int i = 0;
        for (auto e : cr) {
            REQUIRE(e == i);
            ++i;
        }
    }

    {
        auto r = Range(10); // runtime
        int i = 0;
        for (auto e : r) {
            REQUIRE(e == i);
            ++i;
        }
    }
}

