#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"

#include <iostream>
#include <sstream>


TEST_CASE("lambda expression", "[et]")
{
    std::ostringstream oss;

    auto expr = oss << _1;
    expr(1024);
    REQUIRE(oss.str() == "1024");
}
