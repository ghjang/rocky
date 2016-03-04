#include "../catch.hpp"

#include "rocky/base/TypeName.h"

#include <iostream>


TEST_CASE("type_name_of with local class", "[TypeName]")
{
    struct S { };

    REQUIRE("S" == type_name_of<S>);

    S const s{};
    REQUIRE("S const" == type_name_of<decltype(s)>);

    S const volatile s1{};
    REQUIRE("S const volatile" == type_name_of<decltype(s1)>);

    S const volatile * s2{};
    REQUIRE("S const volatile*" == type_name_of<decltype(s2)>);
}

