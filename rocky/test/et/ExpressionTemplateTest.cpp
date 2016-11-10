#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"

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
}
