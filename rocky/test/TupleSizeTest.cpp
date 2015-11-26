#include "catch.hpp"

#include "rocky/meta/TupleSize.h"


TEST_CASE("Getting the size of tuple's template parameters", "[TupleSize]")
{
    using std::tuple;

    static_assert(
            SumOfTupleElementTypeSize<tuple<int, int, int>>() == sizeof(int) * 3,
            "element type size of tuple<int, int, int> == sizeof(int) * 3"
    );

    struct S
    {
        int i_;
        char c_;
    };

    static_assert(
            SumOfTupleElementTypeSize<tuple<int, S, double>>() == sizeof(int) + sizeof(S) + sizeof(double),
            "element type size of tuple<int, S, double> == sizeof(int) + sizeof(S) + sizeof(double)"
    );
}

