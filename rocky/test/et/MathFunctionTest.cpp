#include "../catch.hpp"

#include <cfenv>
#include <tuple>
#include <iostream>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"
#include "rocky/math/NumberCompare.h"


TEST_CASE("number comparison by using is_almost_equal", "[et]")
{
    double d1 = 0;
    double d2 = 0.0;
    REQUIRE(d1 == d2);

    d2 = std::cos(M_PI_2);  // pi / 2
    REQUIRE_FALSE(d1 == d2);
    REQUIRE(is_almost_equal(d1, d2));
    REQUIRE(is_almost_equal(0, d2));
}

// refer to the following for the math constants:
//      https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx
TEST_CASE("trig function terminal", "[et]")
{
    auto arg = std::make_tuple(M_PI_2);
    functor_context<decltype(arg)> c{ arg };

    auto sin = sin_[_1];
    REQUIRE(is_almost_equal(sin(c), 1));

    auto cos = cos_[_1];
    REQUIRE(is_almost_equal(cos(c), 0));

    auto tan = tan_[_1];
    std::feclearexcept(FE_ALL_EXCEPT);
    auto r = tan(c);    // Hmm...
    //std::cout << std::fetestexcept(FE_INVALID) << '\n';
    // TODO: check the validness of return value.
}

TEST_CASE("trig function terminal - 1", "[et]")
{
    auto sin = sin_[_1];
    REQUIRE(is_almost_equal(sin(M_PI_2), 1));

    auto cos = cos_[_1];
    REQUIRE(is_almost_equal(cos(M_PI_2), 0));
}
