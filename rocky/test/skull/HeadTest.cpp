#include "../catch.hpp"

#include "rocky/skull/Head.h"

#include <type_traits>


TEST_CASE("Head", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // empty type list. compile-time error.
    //static_assert(!is_same<int, typename Head<>::type>(), "");

    static_assert(is_same<int, typename Head<int>::type>(), "");

    static_assert(is_same<int, typename Head<int, float, double>::type>(), "");

    static_assert(is_same<int, typename Head<tuple<int, float, double>>::type>(), "");
}

