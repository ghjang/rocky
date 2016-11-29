#include "../catch.hpp"

#include <iostream>

#define ROCKY_ET_STORAGE_POLICY value_storage
#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"
#include "rocky/et/Print.h"


template <typename T>
struct TD;

TEST_CASE("value storage", "[et]")
{
    int i = 10;
    auto expr = i += _1; // NOTE: i's value is copied.

    print_tree(expr, std::cout);

    /*
    TD<decltype(expr)> td;
    expression<
        value_holder<false, int>,
        sum_assign_t,
        place_holder<1>,
        true,
        false,
        value_storage
    >
    */

    // FIXME: this fails. Huh???
    REQUIRE(expr(10) == 20);

    REQUIRE(10 == i);
}
