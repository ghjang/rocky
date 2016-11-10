#include "../catch.hpp"

#include "rocky/skull/Even.h"


TEST_CASE("Even for std::integral_constant", "[skull]")
{
    // expected compile-time error.
    //static_assert(Even<std::tuple<>>());

    static_assert(Even<int_c_t<0>>());
    static_assert(!Even<int_c_t<1>>());
    static_assert(Even<int_c_t<2>>());
    static_assert(!Even<int_c_t<101>>());
}

