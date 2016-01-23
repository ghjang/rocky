#include "../catch.hpp"

#include "rocky/skull/Length.h"


TEST_CASE("Length", "[skull]")
{
    using std::tuple;

    static_assert(0 == Length<>(), "");
    static_assert(0 == Length<TypeList<>>(), "");
    static_assert(0 == Length<tuple<>>(), "");

    static_assert(4 == Length<char, int, float, double>(), "");
    static_assert(4 == Length<TypeList<char, int, float, double>>(), "");
    static_assert(4 == Length<tuple<char, int, float, double>>(), "");
}

