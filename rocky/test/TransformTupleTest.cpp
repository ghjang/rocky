#include "catch.hpp"

#include "rocky/meta/TransformTuple.h"


TEST_CASE("transforming tuple elements", "[TransformTuple]")
{
    using std::tuple;
    using std::make_tuple;

    auto const originalTupleObj = make_tuple('a', 2, 3.0);
    auto const transformedTupleObj = TransformElement(originalTupleObj, [](auto arg) { return arg * 2; });
    REQUIRE(transformedTupleObj == make_tuple('a' * 2, 2 * 2, 3.0 * 2));
}

