#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>


TEST_CASE("left shift", "[et]")
{
    std::ostringstream oss;

    auto expr = oss << _1;
    expr(1024);
    REQUIRE(oss.str() == "1024");

    oss.str("");
    auto expr2 = oss << _1 << " won.";
    expr2(1024);
    REQUIRE(oss.str() == "1024 won.");

    oss.str("");
    auto expr3 = oss << _1 << '.';
    expr3(1024);
    REQUIRE(oss.str() == "1024.");

    oss.str("");
    auto expr4 = oss << _2 << ", " << _1 << ".";
    expr4(10, 24);
    REQUIRE(oss.str() == "24, 10.");

    oss.str("");
    std::vector<int> v{ 10, 20, 30, 40, 50 };
    std::for_each(v.begin(), v.end(), oss << _1 << ',');
    REQUIRE(oss.str() == "10,20,30,40,50,");
    oss.str("");
    std::for_each(v.begin(), v.end(), oss << _1 << ", ");
    REQUIRE(oss.str() == "10, 20, 30, 40, 50, ");
    oss.str("");
    std::for_each(v.begin(), v.end(), oss << _1 << ',' << _1 << ", ");
    REQUIRE(oss.str() == "10,10, 20,20, 30,30, 40,40, 50,50, ");

    oss.str("");
    auto expr5 = _1 << 1;
    auto expr6 = oss << expr5;  // NOTE: expr5 is evaluated first.
    expr6(10);                  // 10 * 2 == 10 << 1
    REQUIRE(oss.str() == "20");

    oss.str("");
    auto expr7 = oss << (_1 << 2);
    expr7(10);
    REQUIRE(oss.str() == "40");
}
