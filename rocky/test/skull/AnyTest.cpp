#include "../catch.hpp"

#include "rocky/skull/Any.h"


TEST_CASE("Any", "[skull]")
{
    using std::is_integral;
    using std::is_floating_point;
    using std::tuple;

    static_assert(!Any<Quote<is_integral>>(), "");
    static_assert(!Any<Quote<is_integral>, TypeList<>>(), "");
    static_assert(!Any<Quote<is_integral>, tuple<>>(), "");

    static_assert(Any<Quote<is_integral>, float, int, double>(), "");
    static_assert(Any<Quote<is_integral>, TypeList<float, int, double>>(), "");
    static_assert(Any<Quote<is_integral>, tuple<float, int, double>>(), "");

    static_assert(!Any<Quote<is_floating_point>, char, int, long>(), "");
    static_assert(!Any<Quote<is_floating_point>, TypeList<char, int, long>>(), "");
    static_assert(!Any<Quote<is_floating_point>, tuple<char, int, long>>(), "");
}

