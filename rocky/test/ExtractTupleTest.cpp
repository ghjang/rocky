#include "catch.hpp"

#include "rocky/meta/ExtractTuple.h"


TEST_CASE("tuple element type extraction", "[ExtractTuple]")
{
    using std::is_same;
    using std::tuple;
    using std::index_sequence;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using extracted_t = tuple<int, uint64_t>;
    static_assert(
            is_same<extracted_t, typename ExtractElementType<index_sequence<1, 3>, tuple_t>::type>(),
            "extracted tuple_t should be same as extracted_t."
    );
}

