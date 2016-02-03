#include "../catch.hpp"

#include "rocky/app/Count.h"


TEST_CASE("counting integral type", "[Count]")
{
    using std::is_integral;

    static_assert(
            Count<is_integral, char, int, float, double, uint64_t>() == 3,
            "the number of integral types is 3."
    );

    static_assert(
            Count<is_integral, TypeList<char, int, float, double, uint64_t>>() == 3,
            "the number of integral types is 3."
    );
}

TEST_CASE("counting pointer type", "[Count]")
{
    using std::is_pointer;
    static_assert(
            Count<is_pointer, char, int *, float, double *, uint64_t>() == 2,
            "the number of pointer types is 2."
    );
}

TEST_CASE("counting integral type of tuple", "[Count]")
{
    using std::tuple;
    using std::is_integral;

    using tuple_t = tuple<char, int, float, double, uint64_t>;
    static_assert(
            Count<is_integral, tuple_t>() == 3,
            "the number of integral types in tuple_t is 3."
    );
}

TEST_CASE("counting pointer type of tuple", "[Count]")
{
    using std::tuple;
    using std::is_pointer;

    using tuple_t = tuple<char, int *, float, double *, uint64_t>;
    static_assert(
            Count<is_pointer, tuple_t>() == 2,
            "the number of pointer types in tuple_t is 2."
    );
}

