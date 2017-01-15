#include "../catch.hpp"

#include <range/v3/all.hpp>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"

#include "rocky/math/NumberSequence.h"


TEST_CASE("number sequence with range and et", "[et]")
{
    using namespace ranges;
    auto generator = number_seq(2 * _1 + 1);
    std::vector<int> seq = view::generate(generator) | view::take(3);
    REQUIRE(ranges::equal(seq, { 1, 3, 5 }));
}

TEST_CASE("number sequence with range and et - 1", "[et]")
{

}
