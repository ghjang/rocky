#include "../catch.hpp"

#include "rocky/app/ReplaceIf.h"


TEST_CASE("replace tuple element type with condition", "[ReplaceIf]")
{
    using std::is_same;
    using std::is_floating_point;
    using std::tuple;

    using tuple_t = tuple<char, int, float, double, int>;
    using replaced_tuple_t = tuple<char, int, int *, int *, int>;

    static_assert(
            is_same<
                    TypeList<char, int, int *, int *, int>,
                    ReplaceIfT<Quote<is_floating_point>, int *, char, int, float, double, int>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, int *, int *, int>,
                    ReplaceIfT<Quote<is_floating_point>, int *, TypeList<char, int, float, double, int>>
            >(),
            ""
    );

    static_assert(
            is_same<replaced_tuple_t, ReplaceIfT<Quote<is_floating_point>, int *, tuple_t>>(),
            "replaced tuple_t should be same as replaced_tuple_t."
    );
}

