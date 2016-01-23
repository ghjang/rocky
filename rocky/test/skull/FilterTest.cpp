#include "../catch.hpp"

#include "rocky/skull/Filter.h"


TEST_CASE("Filter", "[skull]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;

    static_assert(is_same<TypeList<>, FilterT<is_integral>>(), "");
    static_assert(is_same<TypeList<>, FilterT<is_integral, TypeList<>>>(), "");
    static_assert(is_same<tuple<>, FilterT<is_integral, tuple<>>>(), "");

    static_assert(is_same<TypeList<char, int, long>, FilterT<is_integral, char, float, int, double, long>>(), "");
    static_assert(
            is_same<TypeList<char, int, long>, FilterT<is_integral, TypeList<char, float, int, double, long>>>(),
            ""
    );
    static_assert(
            is_same<tuple<char, int, long>, FilterT<is_integral, tuple<char, float, int, double, long>>>(),
            ""
    );
}

