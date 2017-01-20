#include "../catch.hpp"

#include <numeric>
#include <vector>
#include <algorithm>


TEST_CASE("[] operator overloading of std::vector iterator", "[etc]")
{
    std::vector<int> v0{ 10 };
    REQUIRE(v0.size() == 1);    // NOTE: Ooops, be careful...

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);
    REQUIRE(v.size() == 10);

    auto iter = v.begin();
    std::advance(iter, (v.size() / 2) - 1);

    REQUIRE(*iter == 4);
    REQUIRE(iter[0] == 4);
    REQUIRE(iter[-1] == 3);
    REQUIRE(iter[1] == 5);

    iter[0] = 100;
    REQUIRE(*iter == 100);
}
