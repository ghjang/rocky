#include "../catch.hpp"

#include "rocky/skull/Last.h"


TEST_CASE("LastT", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // NOTE: following is an expected compile-time error.
    //static_assert(is_same<double, LastT<>, "");
    //static_assert(is_same<double, LastT<TypeList<>>, "");
    //static_assert(is_same<double, LastT<tuple<>>, "");

    static_assert(is_same<double, LastT<double>>(), "");
    static_assert(is_same<double, LastT<char, int, float, double>>(), "");

    static_assert(is_same<double, LastT<TypeList<double>>>(), "");
    static_assert(is_same<double, LastT<TypeList<char, int, float, double>>>(), "");

    static_assert(is_same<double, LastT<tuple<double>>>(), "");
    static_assert(is_same<double, LastT<tuple<char, int, float, double>>>(), "");
}

