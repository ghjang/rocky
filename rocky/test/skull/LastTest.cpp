#include "../catch.hpp"

#include "rocky/skull/Last.h"


TEST_CASE("Last", "[skull]")
{
    using std::is_same;

    static_assert(is_same<double, Last<char, int, float, double>>(), "");
}

