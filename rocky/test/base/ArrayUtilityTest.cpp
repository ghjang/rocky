#include "../catch.hpp"

#include "rocky/base/ArrayUtility.h"


TEST_CASE("AllExtents", "[ArrayUtility]")
{
    using std::is_same;

    static_assert(is_same<array_extents_t<0>, AllExtentsT<int[]>>(), "");
    static_assert(is_same<array_extents_t<0, 3>, AllExtentsT<int[][3]>>(), "");
    static_assert(is_same<array_extents_t<0, 3, 4>, AllExtentsT<int[][3][4]>>(), "");
    static_assert(is_same<array_extents_t<3, 4, 5>, AllExtentsT<int[3][4][5]>>(), "");
}

TEST_CASE("allExtents", "[ArrayUtility]")
{
    constexpr auto extents = allExtents<int[][3][4]>();
    REQUIRE(extents[0] == 0);
    REQUIRE(extents[1] == 3);
    REQUIRE(extents[2] == 4);
}

