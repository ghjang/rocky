#include "catch.hpp"

#include "rocky/meta/CountTuple.h"


TEST_CASE("counting integral type", "[CountTuple]")
{
    using std::tuple;
    using std::is_integral;

    using tuple_t = tuple<char, int, float, double, uint64_t>;
    static_assert(
            CountElementType<tuple_t, is_integral>() == 3,
            "the number of integral types in tuple_t is 3."
    );
}

TEST_CASE("counting pointer type", "[CountTuple]")
{
    using std::tuple;
    using std::is_pointer;

    using tuple_t = tuple<char, int *, float, double *, uint64_t>;
    static_assert(
            CountElementType<tuple_t, is_pointer>() == 2,
            "the number of pointer types in tuple_t is 2."
    );
}

