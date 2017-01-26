#include "../catch.hpp"

#include "rocky/base/BitOperation.h"


TEST_CASE("count bits", "[base]")
{
    using rocky::base::count_bits;

    // NOTE: 0b01010101 is a C++14 binary literal
    REQUIRE(4 == count_bits(0b01010101));

    REQUIRE(0 == count_bits(0x00));
    REQUIRE(8 == count_bits(0xFF));
    REQUIRE(7 == count_bits(0xFE));
    REQUIRE(4 == count_bits(0x55));

    REQUIRE(16 == count_bits(0xAAAAAAAA));

#pragma pack(push, 1)
    struct S
    {
        int i_ = 0xFF;
        char c_ = 0;
    };
#pragma pack(pop)

    REQUIRE(8 == count_bits(S{}));

    S s{ 0x55, 65 };
    REQUIRE(6 == count_bits(s));
}
