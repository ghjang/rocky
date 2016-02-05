#include "../catch.hpp"

#include "rocky/wolca/FromDigits.h"


TEST_CASE("FromDigits", "[wolca]")
{
    static_assert(0 == FromDigitsT<>(), "");
    static_assert(0 == FromCharDigitsT<>(), "");

    static_assert(1234 == FromDigitsT<1, 2, 3, 4>(), "");
    static_assert(1234 == FromCharDigitsT<'1', '2', '3', '4'>(), "");

    // this is Wolfram Language's FromDigits behavior.
    static_assert(-766 == FromDigitsT<-1, 2, 3, 4>(), "");
    static_assert(-1166 == FromDigitsT<-1, -2, 3, 4>(), "");

    // FromCharDigitsT doesn't support '-' char.
}

