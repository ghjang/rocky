#include "../catch.hpp"

#include "rocky/skull/Pred.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Pred", "[skull]")
{
    static_assert(-1 == Pred<int_c_t<0>>());
    static_assert(-1 == PredV<0>());

    static_assert('a' == Pred<char_c_t<'b'>>());
    static_assert('a' == PredV<'b'>());
}

