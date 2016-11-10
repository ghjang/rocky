#include "../catch.hpp"

#include "rocky/skull/Succ.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Succ", "[skull]")
{
    static_assert(1 == Succ<int_c_t<0>>());
    static_assert(1 == SuccV<0>());

    static_assert('b' == Succ<char_c_t<'a'>>());
    static_assert('b' == SuccV<'a'>());
}

