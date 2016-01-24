#include "../catch.hpp"

#include "rocky/skull/Last.h"


TEST_CASE("Last", "[skull]")
{
    using std::is_same;

    // NOTE: following is an expected compile-time error.
    //static_assert(is_same<double, Last<>, "");

    static_assert(is_same<double, Last<double>>(), "");
    static_assert(is_same<double, Last<char, int, float, double>>(), "");
}

