#include "../catch.hpp"

#include "rocky/skull/Negate.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Negate", "[skull]")
{
    static_assert(-1 == Negate<int_c_t<1>>(), "");
    static_assert(0 == Negate<int_c_t<0>>(), "");
    static_assert(1 == Negate<int_c_t<-1>>(), "");
}

