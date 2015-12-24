#include "../catch.hpp"

#include "rocky/math/RatioString.h"


TEST_CASE("std::ratio compile-time string", "[RatioString]")
{
    using std::ratio;
    using std::string;

    using two_third_t = ratio<2, 3>;
    constexpr auto two_third_str = ToConstExprString(two_third_t());
    REQUIRE(strcmp("2/3", two_third_str) == 0);

    using minus_two_third_t = ratio<-2, 3>;
    constexpr auto minus_two_third_str = ToConstExprString(minus_two_third_t());
    REQUIRE(strcmp("-2/3", minus_two_third_str) == 0);

    using minus_two_third1_t = ratio<2, -3>;
    constexpr auto minus_two_third_str1 = ToConstExprString(minus_two_third1_t());
    REQUIRE(strcmp("-2/3", minus_two_third_str1) == 0);

    using minus_two_third2_t = ratio<-2, -3>;
    constexpr auto minus_two_third_str2 = ToConstExprString(minus_two_third2_t());
    REQUIRE(strcmp("2/3", minus_two_third_str2) == 0);
}

