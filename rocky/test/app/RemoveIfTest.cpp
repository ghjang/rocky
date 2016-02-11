#include "../catch.hpp"

#include "rocky/app/RemoveIf.h"


TEST_CASE("remove tuple element type", "[RemoveIf]")
{
    using std::is_same;
    using std::is_floating_point;
    using std::tuple;

    static_assert(is_floating_point<float>(), "float is floating point type.");
    static_assert(is_floating_point<double>(), "double is floating point type.");
    static_assert(!is_floating_point<char>(), "char is not floating point type.");
    static_assert(!is_floating_point<int>(), "int is not floating point type.");
    static_assert(!is_floating_point<uint64_t>(), "uint64_t is not floating point type.");

    using tuple_t = tuple<char, float, int, double, uint64_t>;
    using removed_t = tuple<char, int, uint64_t>;
    static_assert(
            is_same<removed_t, RemoveIfT<Quote<is_floating_point>, tuple_t>>(),
            "removed tuple_t should be same as removed_t."
    );
}

