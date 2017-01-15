#include "../catch.hpp"

#include <range/v3/all.hpp>

#include "rocky/math/NumberSequence.h"


TEST_CASE("number sequence generator", "[math]")
{
    auto generator = number_seq([](auto x) { return 2 * x + 1; });
    REQUIRE(generator() == 1);
    REQUIRE(generator() == 3);
    REQUIRE(generator() == 5);
}

TEST_CASE("number sequence with range", "[math]")
{
    using namespace ranges;

    auto generator = number_seq([](auto x) { return 2 * x + 1; });
    std::vector<int> seq = view::generate(generator) | view::take(3);
    REQUIRE(ranges::equal(seq, { 1, 3, 5 }));
}
