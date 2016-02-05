#include "../catch.hpp"

#include "rocky/wolca/PadLeft.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("PadLeft", "[wolca]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<0>, int_c_t<0>, int_c_t<0>, int_c_t<0>, int_c_t<0>>,
                    PadLeftT<5, int_c_t<0>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int_c_t<0>, int_c_t<0>, int_c_t<0>, int_c_t<1>, int_c_t<2>>,
                    PadLeftT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    PadLeftT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    PadLeftT<5, int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>, int_c_t<6>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<TL<>, TL<>, int, TL<int_c_t<2>>, int_c_t<3>>,
                    PadLeftT<5, TL<>, TL<int, TL<int_c_t<2>>, int_c_t<3>>>
            >(),
            ""
    );
}

