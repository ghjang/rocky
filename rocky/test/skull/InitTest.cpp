#include "../catch.hpp"

#include "rocky/skull/Init.h"


TEST_CASE("Init", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // empty type list. compile-time error.
    //static_assert(!is_same<int, InitT<>>());

    static_assert(is_same<TypeList<>, InitT<int>>());

    static_assert(is_same<TypeList<int>, InitT<int, float>>());

    static_assert(is_same<TypeList<int, float>, InitT<int, float, double>>());

    static_assert(is_same<TypeList<int, float>, InitT<TypeList<int, float, double>>>());

    static_assert(is_same<tuple<int, float>, InitT<tuple<int, float, double>>>());
}

