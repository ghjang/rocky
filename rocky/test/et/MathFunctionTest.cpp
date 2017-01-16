#include "../catch.hpp"

#include <tuple>

#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"


TEST_CASE("sin function terminal", "[et]")
{
    auto f = sin_[_1];
    auto arg = std::make_tuple(90);
    functor_context<decltype(arg)> c{ arg };
    f(c);
}
