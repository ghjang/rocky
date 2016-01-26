#include "../catch.hpp"

#include "rocky/base/StringNumberConversion.h"


TEST_CASE("char to int", "[StringNumberConversion]")
{
    // expected static asserion fail.
    //static_assert(CharToInt('-') == 0, "expected assertion fail");
    //static_assert(CharToInt('a') == 0, "expected assertion fail");

    static_assert(CharToInt('0') == 0, "'0' should be 0.");
    static_assert(CharToInt('1') == 1, "'1' should be 1.");
    static_assert(CharToInt('7') == 7, "'7' should be 7.");
}

TEST_CASE("char array to int", "[StringNumberConversion]")
{
    // expected static assertion fail.
    //static_assert(CharArrayToInt<'-', 'a', '9', '9'>() == -999, "expected assertion fail");
    //static_assert(CharArrayToInt<'9', '-', '9'>() == -999, "expected assertion fail");

    static_assert(CharArrayToInt<'-', '9', '9', '9'>() == -999, "\"-999\" should be -999.");
    static_assert(CharArrayToInt<'-', '1', '0', '0'>() == -100, "\"-100\" should be -100.");
    static_assert(CharArrayToInt<'0'>() == 0, "\"0\" should be 0.");
    static_assert(CharArrayToInt<'1', '0', '0'>() == 100, "\"100\" should be 100.");
    static_assert(CharArrayToInt<'9', '9', '9'>() == 999, "\"999\" should be 999.");
}

