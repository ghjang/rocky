#include "../catch.hpp"

#include <iostream>

#include <range/v3/all.hpp>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"

#include "rocky/math/NumberSequence.h"


TEST_CASE("number sequence with range and et", "[et]")
{
    using namespace ranges;

    auto generator = number_seq(2 * _1 + 1);
    std::vector<int> seq = view::generate(generator) | view::take(3);
    REQUIRE(ranges::equal(seq, { 1, 3, 5 }));

    auto generator1 = number_seq(2 * _1 + 1, 10);
    std::vector<int> seq1 = view::generate(generator1) | view::take(3);
    REQUIRE(ranges::equal(seq1, { 21, 23, 25 }));

    auto generator2 = number_seq(2 * _1 + 1, 10, 10);
    std::vector<int> seq2 = view::generate(generator2) | view::take(3);
    REQUIRE(ranges::equal(seq2, { 21, 41, 61 }));
}

TEST_CASE("number sequence with range and et - 1", "[et]")
{
    using namespace ranges;

    auto sin = number_seq(sin_[_1], 0, M_PI_2);
    std::vector<double> seq = view::generate(sin) | view::take(4);

    // NOTE: If a generic lambda is used, then it results in a compiler error:
    //
    //          ranges::for_each(seq, [](auto a){ std::cout << a << '\n'; });
    //
    //       The current implementation seems not to handle this case correctly.

    ranges::for_each(seq, [](double a){ std::cout << a << '\n'; });
}
