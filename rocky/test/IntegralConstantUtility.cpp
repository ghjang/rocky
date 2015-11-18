#include "catch.hpp"

#include "rocky/IntegralConstantUtility.h"
#include <iostream>


TEST_CASE("Power", "[IntegralConstantUtility]")
{
    static_assert(Power(10, 0) == 1, "10^0 = 1");
    static_assert(Power(10, 2) == 100, "10^2 = 100");
    static_assert(Power(2, 10) == 1024, "2^10 = 1024");
}

TEST_CASE("+ operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<5> + int_c<5> == int_c<10>, "5 + 5 = 10");
    static_assert(int_c<5> + int_c<5> == std::integral_constant<int, 10>{}, "5 + 5 = 10");
}

TEST_CASE("- operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<15> - int_c<5> == int_c<10>, "15 - 5 = 10");
    static_assert(int_c<15> - int_c<5> == std::integral_constant<int, 10>{}, "15 - 5 = 10");

    static_assert(int_c<15> - int_c<25> == int_c<-10>, "15 - 25 = -10");
    static_assert(int_c<15> - int_c<25> == std::integral_constant<int, -10>{}, "15 - 25 = -10");
}

TEST_CASE("char to int", "[IntegralConstantUtility]")
{
    // expected static asserion fail.
    //static_assert(CharToInt('-') == 0, "expected assertion fail");
    //static_assert(CharToInt('a') == 0, "expected assertion fail");

    static_assert(CharToInt('0') == 0, "'0' should be 0.");
    static_assert(CharToInt('1') == 1, "'1' should be 1.");
    static_assert(CharToInt('7') == 7, "'7' should be 7.");
}

TEST_CASE("char array to int", "[IntegralConstantUtility]")
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

TEST_CASE("user defined literal", "[IntegralConstantUtility]")
{
    static_assert(5_c + 5_c == 10_c, "5 + 5 = 10");
    static_assert(5_c + 5_c == std::integral_constant<int, 10>{}, "5 + 5 = 10");

    static_assert(50_c + 50_c == 100_c, "50 + 50 = 100");
    static_assert(50_c + 50_c == std::integral_constant<int, 100>{}, "50 + 50 = 100");

    static_assert(5_c + -5_c == 0_c, "5 + -5 = 0");
    static_assert(5_c + -5_c == std::integral_constant<int, 0>{}, "5 + -5 = 0");

    static_assert(5_c + -15_c == -10_c, "5 + -15 = -10");
    static_assert(5_c + -15_c == std::integral_constant<int, -10>{}, "5 + -15 = -10");

    static_assert(50_c + -150_c == -100_c, "50 + -150 = -100");
    static_assert(50_c + -150_c == std::integral_constant<int, -100>{}, "50 + -150 = -100");

    static_assert(50_c - 150_c == -100_c, "50 - 150 = -100");
    static_assert(50_c - 150_c == std::integral_constant<int, -100>{}, "50 - 150 = -100");
}

