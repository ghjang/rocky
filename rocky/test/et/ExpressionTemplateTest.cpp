#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"

#include <iostream>
#include <sstream>


template <typename T>
struct TD;

TEST_CASE("lambda expression", "[et]")
{
    std::ostringstream oss;

    auto expr = oss << _1;

    expr(1024);
    REQUIRE(oss.str() == "1024");

    auto expr1 = expr << '\n';
    //expr1();

    //auto expr2 = std::cout << _1 << " won.";

    oss.str("");
    auto expr2 = oss << _1 << '.';
    expr2(1024);
    REQUIRE(oss.str() == "1024.");
}
