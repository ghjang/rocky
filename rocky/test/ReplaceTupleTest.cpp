#include "catch.hpp"

#include "rocky/meta/ReplaceTuple.h"


TEST_CASE("replace tuple element type", "[ReplaceTuple]")
{
    using std::is_same;
    using std::tuple;

    using tuple_t = tuple<char, int, float, double, int>;
    using replaced_tuple_t = tuple<char, int *, float, double, int *>;
    static_assert(
            is_same<replaced_tuple_t, typename ReplaceElementType<tuple_t, int, int *>::type>(),
            "replaced tuple_t should be same as replaced_tuple_t."
    );
}

