#include "../catch.hpp"

#include "rocky/app/Replace.h"


TEST_CASE("replace tuple element type", "[Replace]")
{
    using std::is_same;
    using std::tuple;

    using tuple_t = tuple<char, int, float, double, int>;
    using replaced_tuple_t = tuple<char, int *, float, double, int *>;

    static_assert(
            is_same<
                    TypeList<char, int *, float, double, int *>,
                    ReplaceT<int, int *, char, int, float, double, int>
            >()
    );

    static_assert(
            is_same<
                    TypeList<char, int *, float, double, int *>,
                    ReplaceT<int, int *, TypeList<char, int, float, double, int>>
            >()
    );

    static_assert(
            is_same<replaced_tuple_t, ReplaceT<int, int *, tuple_t>>(),
            "replaced tuple_t should be same as replaced_tuple_t."
    );
}

