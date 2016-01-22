#include "../catch.hpp"

#include "rocky/skull/Head.h"

#include <type_traits>


TEST_CASE("Head", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // empty type list. compile-time error.
    //static_assert(!is_same<int, HeadT<>>(), "");

    static_assert(is_same<int, HeadT<int>>(), "");

    static_assert(is_same<int, HeadT<int, float, double>>(), "");

    static_assert(is_same<int, HeadT<TypeList<int, float, double>>>(), "");

    static_assert(is_same<int, HeadT<tuple<int, float, double>>>(), "");
}

