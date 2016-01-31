#include "../catch.hpp"

#include "rocky/skull/SplitAt.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("SplitAt", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TypeList<TypeList<>, TypeList<>>, SplitAtT<int_c_t<0>>>(), "");
    static_assert(is_same<TypeList<TypeList<>, TypeList<>>, SplitAtT<int_c_t<2>>>(), "");

    static_assert(
            is_same<
                    TypeList<
                            TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>, TypeList<>
                    >,
                    SplitAtT<int_c_t<5>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<
                            TypeList<int_c_t<1>, int_c_t<2>>, TypeList<int_c_t<3>, int_c_t<4>, int_c_t<5>>
                    >,
                    SplitAtT<int_c_t<2>, int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<
                            TypeList<int_c_t<1>, int_c_t<2>>, TypeList<int_c_t<3>, int_c_t<4>, int_c_t<5>>
                    >,
                    SplitAtT<int_c_t<2>, TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<
                            TypeList<int_c_t<1>, int_c_t<2>>, TypeList<int_c_t<3>, int_c_t<4>, int_c_t<5>>
                    >,
                    SplitAtT<int_c_t<2>, tuple<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>>
            >(),
            ""
    );
}

