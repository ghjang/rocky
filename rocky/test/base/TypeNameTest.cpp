#include "../catch.hpp"

#include "rocky/base/TypeName.h"

#include <iostream>
#include <vector>


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

TEST_CASE("template_name_of", "[TypeName]")
{
    using std::tuple;
    using std::vector;

    using vector_t = vector<char>;
    using vector_c_t = vector<char> const;
    using vector_cv_t = vector<char> const volatile;
    using vector_p_t = vector<char> *;

    REQUIRE("vector" == template_name_of<vector_t>);
    REQUIRE("vector" == template_name_of<vector_c_t>);
    REQUIRE("vector" == template_name_of<vector_cv_t>);
    REQUIRE("" == template_name_of<vector_p_t>);

    using tuple_t = tuple<char, int, float, double>;
    REQUIRE("tuple" == template_name_of<tuple_t>);
}

