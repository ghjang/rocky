#include "../catch.hpp"

#include <tuple>
#include <iostream>

#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"


// refer to the following for the math constants:
//  https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx
TEST_CASE("sin function terminal", "[et]")
{
    auto f = sin_[_1];
    auto arg = std::make_tuple(M_PI_2);
    functor_context<decltype(arg)> c{ arg };
    REQUIRE(1 == f(c));
}
