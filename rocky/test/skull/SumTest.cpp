#include "../catch.hpp"

#include "rocky/skull/Sum.h"


TEST_CASE("Sum", "[skull]")
{
    using std::tuple;

    static_assert(15 == Sum<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>(), "");
    static_assert(15 == Sum<TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");
    static_assert(15 == Sum<tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");
}

