#include "catch.hpp"

#include "rocky/NthTupleElementType.h"


TEST_CASE("N-th tuple element type", "[NthTupleType]")
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

    struct A { };
    struct B { int i; };
    struct C { using type = int; };
    struct D { void f() { } };
    using t1 = tuple<char, A, short, B, int, C, float, D, double>;
    static_assert(is_same<NthTupleElementType<t1, 0>::type, char>::value, "t1's 0-th should be char.");
    static_assert(is_same<NthTupleElementType<t1, 1>::type, A>::value, "t1's 1-th should be struct A.");
    static_assert(is_same<NthTupleElementType<t1, 2>::type, short>::value, "t1's 2-th should be char.");
    static_assert(is_same<NthTupleElementType<t1, 3>::type, B>::value, "t1's 3-th should be struct B.");
    static_assert(is_same<NthTupleElementType<t1, 4>::type, int>::value, "t1's 4-th should be char.");
    static_assert(is_same<NthTupleElementType<t1, 5>::type, C>::value, "t1's 5-th should be struct C.");
    static_assert(is_same<NthTupleElementType<t1, 6>::type, float>::value, "t1's 6-th should be char.");
    static_assert(is_same<NthTupleElementType<t1, 7>::type, D>::value, "t1's 7-th should be struct D.");
    static_assert(is_same<NthTupleElementType<t1, 8>::type, double>::value, "t1's 8-th should be char.");

    //static_assert(is_same<NthTupleElementType<t1, -1>::type, double>::value, "this is a static assertion failure.");
    //static_assert(is_same<NthTupleElementType<t1, 9>::type, double>::value, "this is a static assertion failure.");
}

