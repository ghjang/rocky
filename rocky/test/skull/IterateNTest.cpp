#include "../catch.hpp"

#include "rocky/skull/IterateN.h"

#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/base/TypeComposition.h"


namespace
{
    template <typename x>
    using TwiceT = IterateNT<Bind2nd<Quote<Multiply>, int_c_t<2>>, x, 2>;
} // un-named namespace


TEST_CASE("IterateNT, Twice", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<4>>,
                    TwiceT<int_c_t<1>>
            >(),
            ""
    );
}

