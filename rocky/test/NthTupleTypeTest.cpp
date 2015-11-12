#include "catch.hpp"

#include "rocky/NthTupleType.h"


TEST_CASE("N-th tuple element type", "[tuple]")
{
    using std::tuple;
    using std::is_same;

    using t = tuple<char, short, int, float, double>;
    static_assert(is_same<NthTupleElementType<t, 0>::type, char>::value, "t's 0-th should be char.");
    static_assert(is_same<NthTupleElementType<t, 1>::type, short>::value, "t's 1-th should be char.");
    static_assert(is_same<NthTupleElementType<t, 2>::type, int>::value, "t's 2-th should be char.");
    static_assert(is_same<NthTupleElementType<t, 3>::type, float>::value, "t's 3-th should be char.");
    static_assert(is_same<NthTupleElementType<t, 4>::type, double>::value, "t's 4-th should be char.");

    //static_assert(is_same<NthTupleElementType<t, -1>::type, double>::value, "this is a static assertion failure.");
    //static_assert(is_same<NthTupleElementType<t, 5>::type, double>::value, "this is a static assertion failure.");

}

