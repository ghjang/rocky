#include "../catch.hpp"

#include "rocky/wolca/Fold.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("wolca fold left, integral constant sum", "[wolca]")
{
    using sum_t = FoldT<
                        Plus,
                        int_c_t<0>,  // init
                        int_c_t<1>,
                        int_c_t<2>,
                        int_c_t<3>,
                        int_c_t<4>,
                        int_c_t<5>
                    >;
    static_assert(sum_t() == 15, "(((((0 + 1) + 2) + 3) + 4) + 5) = 15");
}

