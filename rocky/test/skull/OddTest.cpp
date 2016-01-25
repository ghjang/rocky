#include "../catch.hpp"

#include "rocky/skull/Odd.h"


TEST_CASE("Odd for std::integral_constant", "[skull]")
{
    // expected compile-time error.
    //static_assert(Odd<std::tuple<>>(), "");

    static_assert(!Odd<int_c_t<0>>(), "");
    static_assert(Odd<int_c_t<1>>(), "");
    static_assert(!Odd<int_c_t<2>>(), "");
    static_assert(Odd<int_c_t<101>>(), "");
}

