#include "../catch.hpp"

#include <iostream>

#define ROCKY_ET_STORAGE_POLICY value_storage
#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"


// NOTE: This is OK.
TEST_CASE("value storage, -= operator", "[et]")
{
    int i = 10;
    auto expr = i -= _1; // NOTE: i's value is copied.

    REQUIRE(expr(3) == 7);
    REQUIRE(10 == i);
}

// NOTE: This is NOT OK. A clang compiler bug??
TEST_CASE("value storage, += operator", "[et]")
{
    int i = 10;

    auto expr = i += _1; // NOTE: i's value is copied.

    // FIXME: This fails. Huh?? A compiler bug??
    REQUIRE(expr(3) == 13);

    REQUIRE(10 == i);
}
