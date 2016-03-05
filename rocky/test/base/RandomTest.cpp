#include "../catch.hpp"

#include "rocky/base/Random.h"

#include "rocky/base/TypeName.h"


TEST_CASE("ANSI-Compliant Predefined Macros", "[Random]")
{
    // NOTE: on clang

    /*
    REQUIRE("char const (&) [12]" == name_of<decltype(__DATE__)>);
    REQUIRE("char const (&) [61]" == name_of<decltype(__FILE__)>);
    REQUIRE("char const [30]" == name_of<decltype(__func__)>);
    REQUIRE("int" == name_of<decltype(__LINE__)>);
    REQUIRE("int" == name_of<decltype(__STDC__)>);
    REQUIRE("char const (&) [9]" == name_of<decltype(__TIME__)>);
    REQUIRE("char const (&) [25]" == name_of<decltype(__TIMESTAMP__)>);
     */
}

TEST_CASE("constexpr staticRand", "[Random]")
{
    // NOTE: well, I don't know that this is a proper condition to check.
    static_assert(staticRand() > 0, "");

    REQUIRE(staticRand() > 0);
}

