#include "../catch.hpp"

#include "rocky/meta/TypeListToTuple.h"


TEST_CASE("", "[meta]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<tuple<>, TypeListToTupleT<TypeList<>>>(), "");
    static_assert(is_same<tuple<char, int>, TypeListToTupleT<TypeList<char, int>>>(), "");
    static_assert(!is_same<TypeList<char, int>, TypeListToTupleT<TypeList<char, int>>>(), "");
}

