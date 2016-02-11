#include "../catch.hpp"

#include "rocky/wolca/NestList.h"

#include "rocky/base/IntegerSequenceUtility.h"
#include "rocky/base/TypeUtility.h"
#include "rocky/skull/Sum.h"


TEST_CASE("NestList", "[wolca]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TL<int_c_t<1>, int_c_t<2>, int_c_t<4>, int_c_t<8>>,
                    NestListT<Bind2nd<Quote<Multiply>, int_c_t<2>>, int_c_t<1>, 3>
            >(),
            ""
    );

    static_assert(15 == SumT<NestListT<Bind2nd<Quote<Multiply>, int_c_t<2>>, int_c_t<1>, 3>>(), "");

    static_assert(
            is_same<
                    integer_sequence<int, 1, 2, 4, 8>,
                    IntConstListToIntSeqT<NestListT<Bind2nd<Quote<Multiply>, int_c_t<2>>, int_c_t<1>, 3>>
            >(),
            ""
    );
}

