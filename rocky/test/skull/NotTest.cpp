#include "../catch.hpp"

#include "rocky/skull/Not.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Not", "[skull]")
{
    using std::true_type;
    using std::false_type;

    static_assert(false == Not<true_type>(), "");
    static_assert(true == Not<false_type>(), "");

    static_assert(false == Not<int_c_t<10>>(), "");
    static_assert(true == Not<int_c_t<0>>(), "");
}

