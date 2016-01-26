#include "../catch.hpp"

#include "rocky/base/TypeAt.h"


TEST_CASE("TypeAt", "[TypeAt]")
{
    using std::is_same;
    using std::tuple;

    // out-of-range index. compile-time error.
    //static_assert(is_same<char, TypeAtT<0>>(), "");
    //static_assert(is_same<char, TypeAtT<1>>(), "");
    //static_assert(is_same<char, TypeAtT<0, TypeList<>>>(), "");
    //static_assert(is_same<char, TypeAtT<1, TypeList<>>>(), "");
    //static_assert(is_same<char, TypeAtT<0, tuple<>>>(), "");
    //static_assert(is_same<char, TypeAtT<1, tuple<>>>(), "");

    static_assert(is_same<char, TypeAtT<0, char, int, float, double>>(), "");
    static_assert(is_same<int, TypeAtT<1, char, int, float, double>>(), "");
    static_assert(is_same<double, TypeAtT<3, char, int, float, double>>(), "");

    // out-of-range index. compile-time error.
    //static_assert(is_same<int, TypeAtT<4, char, int, float, double>>(), "");
    //static_assert(is_same<int, TypeAtT<4, TypeList<char, int, float, double>>>(), "");
    //static_assert(is_same<int, TypeAtT<4, tuple<char, int, float, double>>>(), "");

    static_assert(is_same<char, TypeAtT<0, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<int, TypeAtT<1, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<double, TypeAtT<3, TypeList<char, int, float, double>>>(), "");

    static_assert(is_same<char, TypeAtT<0, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<int, TypeAtT<1, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<double, TypeAtT<3, tuple<char, int, float, double>>>(), "");
}

