#include "../catch.hpp"

#include "rocky/wolca/Rotate.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("RotateLeftT, RotateRightT", "[wolca]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TypeList<char, int, int64_t, float, double>,
                    RotateLeftT<0, char, int, int64_t, float, double>
            >()
    );

    static_assert(
            is_same<
                    TypeList<int, int64_t, float, double, char>,
                    RotateLeftT<1, char, int, int64_t, float, double>
            >()
    );

    static_assert(
            is_same<
                    TypeList<double, char, int, int64_t, float>,
                    RotateRightT<1, char, int, int64_t, float, double>
            >()
    );
}

