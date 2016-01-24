#include "../catch.hpp"

#include "rocky/skull/Product.h"


TEST_CASE("Product for std::integral_constant", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(120 == ProductT<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>(), "");
    static_assert(120 == ProductT<TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");
    static_assert(120 == ProductT<tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");

    static_assert(
            is_same<int_c_t<120>, ProductT<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), ""
    );
    static_assert(
            is_same<int_c_t<120>, ProductT<TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>>(), ""
    );
    static_assert(
            is_same<int_c_t<120>, ProductT<tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>>(), ""
    );
}

