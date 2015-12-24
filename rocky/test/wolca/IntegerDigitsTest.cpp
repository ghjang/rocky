#include "../catch.hpp"

#include "rocky/wolca/IntegerDigits.h"


TEST_CASE("IntegerDigits runtime","[wolca]")
{
    auto digits = IntegerDigits(123456789);
    int n = 1;
    for (auto i : digits) {
        REQUIRE(n == i);
        ++n;
    }

    auto digits1 = IntegerDigits(-123456789);
    n = 1;
    for (auto i : digits1) {
        REQUIRE(n == i);
        ++n;
    }

    auto digits2 = IntegerDigits(3456);
    n = 3;
    for (auto i : digits2) {
        REQUIRE(n == i);
        ++n;
    }

    auto digits3 = IntegerDigits(2468);
    n = 2;
    for (auto i : digits3) {
        REQUIRE(n == i);
        n += 2;
    }
}

TEST_CASE("IntegerDigit","[wolca]")
{
    // NOTE: this is an expected static assertion failures.
    //static_assert(5 == IntegerDigit(12345, IntegerLength(12345), 0), "");
    //static_assert(5 == IntegerDigit(12345, IntegerLength(12345), 6), "");

    static_assert(5 == IntegerDigit(12345, IntegerLength(12345), 1), "");
    static_assert(1 == IntegerDigit(12345, IntegerLength(12345), 5), "");

    static_assert(5 == IntegerDigit(-12345, IntegerLength(-12345), 1), "");
    static_assert(1 == IntegerDigit(-12345, IntegerLength(-12345), 5), "");
}

