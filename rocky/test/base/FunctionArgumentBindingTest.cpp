#include "../catch.hpp"

#include "rocky/base/FunctionArgumentBinding.h"

#include "rocky/base/FunctionComposition.h"


namespace
{
    int f(int i) { return i * 2; }
    int g(int a, int b, int c) { return a * b + c; }
    int h(int i) { return i % 5; }
} // un-named namespace


TEST_CASE("bind_first", "[FunctionArgumentBinding]")
{
    auto fs = bind_first(g);
    REQUIRE(5 == fs(1, 2, 3));

    auto fs1 = bind_first(g, 5);
    REQUIRE(31 == fs1(5, 6));

    auto fs2 = bind_first(g, 5, 6, 7);
    REQUIRE(37 == fs2());

    auto fs3 = compose(f, bind_first(g, 5, 6));
    REQUIRE(74 == fs3(7));

    auto fs4 = compose(f, bind_first(g, 5, 6), h);
    REQUIRE(64 == fs4(7));
}

TEST_CASE("bind_last", "[FunctionArgumentBinding]")
{
    auto fs = bind_last(g);
    REQUIRE(5 == fs(1, 2, 3));

    auto fs1 = bind_last(g, 5);
    REQUIRE(35 == fs1(5, 6));

    auto fs2 = bind_last(g, 5, 6, 7);
    REQUIRE(37 == fs2());

    auto fs3 = compose(f, bind_last(g, 5, 6));
    REQUIRE(82 == fs3(7));

    auto fs4 = compose(f, bind_last(g, 5, 6), h);
    REQUIRE(32 == fs4(7));
}

