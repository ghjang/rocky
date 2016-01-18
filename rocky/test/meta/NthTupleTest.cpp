#include "../catch.hpp"

#include "rocky/meta/NthTuple.h"


TEST_CASE("N-th element type", "[NthTuple]")
{
    using std::is_same;

    static_assert(is_same<NthElementType<0, char, short, int, float, double>::type, char>(), "0-th should be char.");
    static_assert(is_same<NthElementType<1, char, short, int, float, double>::type, short>(), "1-th should be char.");
    static_assert(is_same<NthElementType<2, char, short, int, float, double>::type, int>(), "2-th should be char.");
    static_assert(is_same<NthElementType<3, char, short, int, float, double>::type, float>(), "3-th should be char.");
    static_assert(is_same<NthElementType<4, char, short, int, float, double>::type, double>(), "4-th should be char.");

    /*
    static_assert(
            is_same<NthElementType<-1, char, short, int, float, double>::type, double>(),
            "this is a static assertion failure."
    );
    static_assert(
            is_same<NthElementType<5, char, short, int, float, double>::type, double>(),
            "this is a static assertion failure."
    );
    */

    struct A { };
    struct B { int i; };
    struct C { using type = int; };
    struct D { void f() { } };
    static_assert(
            is_same<NthElementType<0, char, A, short, B, int, C, float, D, double>::type, char>(),
            "0-th should be char."
    );
    static_assert(
            is_same<NthElementType<1, char, A, short, B, int, C, float, D, double>::type, A>(),
            "1-th should be struct A."
    );
    static_assert(
            is_same<NthElementType<2, char, A, short, B, int, C, float, D, double>::type, short>(),
            "2-th should be char."
    );
    static_assert(
            is_same<NthElementType<3, char, A, short, B, int, C, float, D, double>::type, B>(),
            "3-th should be struct B."
    );
    static_assert(
            is_same<NthElementType<4, char, A, short, B, int, C, float, D, double>::type, int>(),
            "4-th should be char."
    );
    static_assert(
            is_same<NthElementType<5, char, A, short, B, int, C, float, D, double>::type, C>(),
            "5-th should be struct C."
    );
    static_assert(
            is_same<NthElementType<6, char, A, short, B, int, C, float, D, double>::type, float>(),
            "6-th should be char."
    );
    static_assert(
            is_same<NthElementType<7, char, A, short, B, int, C, float, D, double>::type, D>(),
            "7-th should be struct D."
    );
    static_assert(
            is_same<NthElementType<8, char, A, short, B, int, C, float, D, double>::type, double>(),
            "8-th should be char."
    );

    /*
    static_assert(
            is_same<NthElementType<-1, char, A, short, B, int, C, float, D, double>::type, double>(),
            "this is a static assertion failure."
    );
    static_assert(
            is_same<NthElementType<9, char, A, short, B, int, C, float, D, double>::type, double>(),
            "this is a static assertion failure."
    );
    */
}

TEST_CASE("N-th tuple element type", "[NthTuple]")
{
    using std::tuple;
    using std::is_same;

    using t = tuple<char, short, int, float, double>;
    static_assert(is_same<NthElementType<0, t>::type, char>(), "t's 0-th should be char.");
    static_assert(is_same<NthElementType<1, t>::type, short>(), "t's 1-th should be char.");
    static_assert(is_same<NthElementType<2, t>::type, int>(), "t's 2-th should be char.");
    static_assert(is_same<NthElementType<3, t>::type, float>(), "t's 3-th should be char.");
    static_assert(is_same<NthElementType<4, t>::type, double>(), "t's 4-th should be char.");

    //static_assert(is_same<NthElementType<-1, t>::type, double>(), "this is a static assertion failure.");
    //static_assert(is_same<NthElementType<5, t>::type, double>(), "this is a static assertion failure.");

    struct A { };
    struct B { int i; };
    struct C { using type = int; };
    struct D { void f() { } };
    using t1 = tuple<char, A, short, B, int, C, float, D, double>;
    static_assert(is_same<NthElementType<0, t1>::type, char>(), "t1's 0-th should be char.");
    static_assert(is_same<NthElementType<1, t1>::type, A>(), "t1's 1-th should be struct A.");
    static_assert(is_same<NthElementType<2, t1>::type, short>(), "t1's 2-th should be char.");
    static_assert(is_same<NthElementType<3, t1>::type, B>(), "t1's 3-th should be struct B.");
    static_assert(is_same<NthElementType<4, t1>::type, int>(), "t1's 4-th should be char.");
    static_assert(is_same<NthElementType<5, t1>::type, C>(), "t1's 5-th should be struct C.");
    static_assert(is_same<NthElementType<6, t1>::type, float>(), "t1's 6-th should be char.");
    static_assert(is_same<NthElementType<7, t1>::type, D>(), "t1's 7-th should be struct D.");
    static_assert(is_same<NthElementType<8, t1>::type, double>(), "t1's 8-th should be char.");

    //static_assert(is_same<NthElementType<-1, t1>::type, double>(), "this is a static assertion failure.");
    //static_assert(is_same<NthElementType<9, t1>::type, double>(), "this is a static assertion failure.");
}

