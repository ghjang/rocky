#include "../catch.hpp"

#include "rocky/meta/Extract.h"


TEST_CASE("tuple element type extraction", "[Extract]")
{
    using std::is_same;
    using std::tuple;
    using std::index_sequence;

    static_assert(
            is_same<
                    TypeList<int, uint64_t>,
                    ExtractT<index_sequence<1, 3>, char, int, double, uint64_t, float>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<int, uint64_t>,
                    ExtractT<index_sequence<1, 3>, TypeList<char, int, double, uint64_t, float>>
            >(),
            ""
    );

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using extracted_t = tuple<int, uint64_t>;
    static_assert(
            is_same<extracted_t, ExtractT<index_sequence<1, 3>, tuple_t>>(),
            "extracted tuple_t should be same as extracted_t."
    );
}

