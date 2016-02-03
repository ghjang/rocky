#include "../catch.hpp"

#include "rocky/skull/ZipWith.h"

#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/skull/Replicate.h"
#include "rocky/skull/Range.h"
#include "rocky/skull/Max.h"


TEST_CASE("ZipWith Plus", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<2>, int_c_t<4>, int_c_t<6>>,
                    ZipWithT<
                            Plus,
                            TL<int_c_t<1>, int_c_t<2>, int_c_t<3>>,
                            TL<int_c_t<1>, int_c_t<2>, int_c_t<3>>
                    >
            >(),
            ""
    );
}

TEST_CASE("ZipWith Max", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<6>, int_c_t<7>, int_c_t<8>>,
                    ZipWithT<
                            Max,
                            TL<int_c_t<4>, int_c_t<7>, int_c_t<8>>,
                            TL<int_c_t<6>, int_c_t<1>, int_c_t<7>>
                    >
            >(),
            ""
    );
}

TEST_CASE("ZipWith Multiply", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<2>, int_c_t<4>, int_c_t<6>, int_c_t<8>, int_c_t<10>>,
                    ZipWithT<
                            Multiply,
                            ReplicateT<5, int_c_t<2>>,
                            RangeT<int_c_t<1>, int_c_t<5>>
                    >
            >(),
            ""
    );
}

