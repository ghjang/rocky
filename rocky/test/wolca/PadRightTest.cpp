#include "../catch.hpp"

#include "rocky/wolca/PadRight.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("PadRight", "[wolca]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<0>, int_c_t<0>, int_c_t<0>, int_c_t<0>, int_c_t<0>>,
                    PadRightT<5, int_c_t<0>>
            >()
    );

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<0>, int_c_t<0>, int_c_t<0>>,
                    PadRightT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>>
            >()
    );

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    PadRightT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>
            >()
    );

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    PadRightT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>, int_c_t<6>>
            >()
    );

    static_assert(
            is_same<
                    TL<int, TL<int_c_t<2>>, int_c_t<3>, TL<>, TL<>>,
                    PadRightT<5, TL<>, TL<int, TL<int_c_t<2>>, int_c_t<3>>>
            >()
    );
}

