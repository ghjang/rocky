#include "../catch.hpp"

#include "rocky/base/ConstExprArray.h"


namespace
{
    template <std::size_t ArraySize>
    constexpr auto CalculateSquare()
    {
        ConstExprArray<int, ArraySize> result;
        for (int i = 0; i < result.size(); ++i) {
            result[i] = i * i;  // NOTE: this is not allowed in C++14 std::array.
        }
        return result;
    }
}


TEST_CASE("basic usage in constexpr function", "[ConstExprArray]")
{
    constexpr auto resultArray = CalculateSquare<5>();
    REQUIRE(resultArray[0] == 0);
    REQUIRE(resultArray[1] == 1);
    REQUIRE(resultArray[2] == 4);
    REQUIRE(resultArray[3] == 9);
    REQUIRE(resultArray[4] == 16);
}

