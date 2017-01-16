#include "../catch.hpp"

#include <limits>
#include <cfenv>
#include <tuple>
#include <iostream>

#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"

namespace
{
    // refer to the following for floating point number comparison:
    //      http://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
    template
    <
        typename T, typename U,
        typename = std::enable_if_t<std::is_floating_point<std::common_type_t<T, U>>::value>
    >
    bool is_same(T a, U b)
    {
        return std::fabs(a - b) < std::numeric_limits<decltype(a - b)>::epsilon();
    }

    template
    <
        typename T, typename U,
        typename dummy = void,
        typename = std::enable_if_t<std::is_integral<std::common_type_t<T, U>>::value>
    >
    bool is_same(T a, U b)
    {
        return a == b;
    }
} // un-named namespace


TEST_CASE("number comparison by using is_same", "[et]")
{
    double d1 = 0;
    double d2 = 0.0;
    REQUIRE(d1 == d2);

    d2 = std::cos(M_PI_2);  // pi / 2
    REQUIRE_FALSE(d1 == d2);
    REQUIRE(is_same(d1, d2));
    REQUIRE(is_same(0, d2));
}

// refer to the following for the math constants:
//      https://msdn.microsoft.com/en-us/library/4hwaceh6.aspx
TEST_CASE("trig function terminal", "[et]")
{
    auto arg = std::make_tuple(M_PI_2);
    functor_context<decltype(arg)> c{ arg };

    auto sin = sin_[_1];
    REQUIRE(is_same(sin(c), 1));

    auto cos = cos_[_1];
    REQUIRE(is_same(cos(c), 0));

    auto tan = tan_[_1];
    std::feclearexcept(FE_ALL_EXCEPT);
    auto r = tan(c);    // Hmm...
    //std::cout << std::fetestexcept(FE_INVALID) << '\n';
    // TODO: check the validness of return value.
}
