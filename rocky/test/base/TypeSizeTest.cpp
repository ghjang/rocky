#include "../catch.hpp"

#include "rocky/meta/TypeSize.h"


TEST_CASE("Getting the sum of template parameter type sizes", "[TypeSize]")
{
    static_assert(
            SumOfTypeSize<int, int, int>() == sizeof(int) * 3,
            "element type size of <int, int, int> == sizeof(int) * 3"
    );

    struct S
    {
        int i_;
        char c_;
    };

    static_assert(
            SumOfTypeSize<int, S, double>() == sizeof(int) + sizeof(S) + sizeof(double),
            "element type size of <int, S, double> == sizeof(int) + sizeof(S) + sizeof(double)"
    );
}

TEST_CASE("Getting the size of tuple's template parameters", "[TypeSize]")
{
    using std::tuple;

    static_assert(
            SumOfTypeSize<tuple<int, int, int>>() == sizeof(int) * 3,
            "element type size of tuple<int, int, int> == sizeof(int) * 3"
    );

    struct S
    {
        int i_;
        char c_;
    };

    static_assert(
            SumOfTypeSize<tuple<int, S, double>>() == sizeof(int) + sizeof(S) + sizeof(double),
            "element type size of tuple<int, S, double> == sizeof(int) + sizeof(S) + sizeof(double)"
    );
}

TEST_CASE("n-th element type size", "[TypeSize]")
{
    using std::tuple;

    static_assert(
            sizeof(float) == NthTypeSize<2, int, char, float, double, uint64_t>(),
            "3rd element's size == sizeof(float)"
    );

    using tuple_t = tuple<int, char, float, double, uint64_t>;
    static_assert(
            sizeof(double) == NthTypeSize<3, tuple_t>(),
            "4-th element's size == sizeof(double)"
    );
}

