#include "../catch.hpp"

#include "rocky/skull/Tail.h"


TEST_CASE("Tail", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // empty type list. compile-time error.
    //static_assert(!is_same<TypeList<>, TailT<>>());

    static_assert(is_same<TypeList<>, TailT<int>>());

    static_assert(is_same<TypeList<float, double>, TailT<int, float, double>>());

    static_assert(is_same<tuple<float, double>, TailT<tuple<int, float, double>>>());

    static_assert(is_same<tuple<float, double>, TailT<tuple<int, float, double>>>());
}

