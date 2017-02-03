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

TEST_CASE("number sequence with range and calculator", "[math]")
{
    using namespace ranges;
    using rocky::math::calc::number_t;
    using rocky::math::calc::to_int;

    auto gen = calc_seq("x^2 + 2 * x + 1");
    std::vector<int> seq = view::generate(gen)
                                | view::take(3)
                                | view::transform([](number_t const& n){ return to_int(n); });
    REQUIRE(ranges::equal(seq, { 1, 4, 9 }));
}
