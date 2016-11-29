#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"


TEST_CASE("default storage", "[et]")
{
    int i = 10;
    auto expr = i += _1; // NOTE: reference to i will be stored in the expression.
    REQUIRE(expr(10) == 20);
    REQUIRE(20 == i);
}
