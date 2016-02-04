#include "../catch.hpp"

#include "rocky/wolca/Nest.h"

#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/base/TypeUtility.h"


TEST_CASE("Nest", "[wolca]")
{
    using std::is_same;

    static_assert(
            is_same<
                    int_c_t<8>,
                    NestT<Bind2nd<Multiply, int_c_t<2>>::template Convert, int_c_t<1>, 3>
            >(),
            ""
    );
}
