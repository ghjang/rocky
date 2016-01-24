#include "../catch.hpp"

#include "rocky/skull/Sum.h"


TEST_CASE("Sum", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(15 == SumT<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>(), "");
    static_assert(15 == SumT<TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");
    static_assert(15 == SumT<tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), "");

    static_assert(
            is_same<int_c_t<15>, SumT<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>(), ""
    );
    static_assert(
            is_same<int_c_t<15>, SumT<TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>>(), ""
    );
    static_assert(
            is_same<int_c_t<15>, SumT<tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>>(), ""
    );
}

