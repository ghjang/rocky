#include "../catch.hpp"

#include "rocky/wolca/Range.h"


TEST_CASE("Range function", "[wolca]")
{
    {
        int i = 0;
        for (auto e : RangeT<10>::value) {  // compile-time
            REQUIRE(e == i);
            ++i;
        }
    }

    {
        int i = 0;
        for (auto e : Range<10>()) {        // compile-time
            REQUIRE(e == i);
            ++i;
        }
    }

    {
        int i = 0;
        for (auto e : Range(10)) {          // runtime
            REQUIRE(e == i);
            ++i;
        }
    }
}

