#include "../catch.hpp"

#include "rocky/base/FindIf.h"


TEST_CASE("FindIf", "[skull]")
{
    using std::is_floating_point;
    using std::tuple;

    static_assert(-1 == FindIf<is_floating_point>(), "");
    static_assert(-1 == FindIf<is_floating_point, TypeList<>>(), "");
    static_assert(-1 == FindIf<is_floating_point, tuple<>>(), "");

    static_assert(-1 == FindIf<is_floating_point, char, int>(), "");
    static_assert(-1 == FindIf<is_floating_point, TypeList<char, int>>(), "");
    static_assert(-1 == FindIf<is_floating_point, tuple<char, int>>(), "");

    static_assert(2 == FindIf<is_floating_point, char, int, float, double>(), "");
    static_assert(2 == FindIf<is_floating_point, TypeList<char, int, float, double>>(), "");
    static_assert(2 == FindIf<is_floating_point, tuple<char, int, float, double>>(), "");
}

