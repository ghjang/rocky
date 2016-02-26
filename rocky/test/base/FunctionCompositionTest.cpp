#include "../catch.hpp"

#include "rocky/base/FunctionComposition.h"


namespace
{
    int f(int a)
    {
        return a * 2;
    }

    int g(int a)
    {
        return a + 1;
    }
} // un-named namespace


TEST_CASE("compose", "[FunctionComposition]")
{
    auto fs = compose(f, g);
    REQUIRE(4 == fs(1));

    auto fs1 = compose(f, g, []{ return 10; });
    REQUIRE(22 == fs1());

    auto fs2 = compose(f, g, [](int i){ return i - 1; });
    REQUIRE(40 == fs2(20));

    struct S
    {
        auto operator () (int i) const
        { return i + 5; }
    };

    auto fs3 = compose(f, g, [](int i){ return i - 1; }, S());
    REQUIRE(16 == fs3(3));

    std::function<int(int)> objF = [](int i){ return i % 10; };

    auto fs4 = compose(f, g, [](int i){ return i - 1; }, S(), objF);
    REQUIRE(20 == fs4(15));

    // C++17 fold expression
    auto sum = [](auto... xs) { return (xs + ...); };

    auto fs5 = compose(f, g, [](int i){ return i - 1; }, S(), objF, sum);
    REQUIRE(20 == fs5(1, 2, 3, 4, 5));
}

