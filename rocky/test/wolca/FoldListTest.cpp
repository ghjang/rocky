#include "../catch.hpp"

#include "rocky/wolca/FoldList.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("wolca fold-list-left, integral constant sum", "[wolca]")
{
    using std::is_same;

    // (((((0 + 1) + 2) + 3) + 4) + 5) = 15
    using sum_list_0_t = FoldListT<
                            Plus,
                            int_c_t<0>,  // init
                            int_c_t<1>,
                            int_c_t<2>,
                            int_c_t<3>,
                            int_c_t<4>,
                            int_c_t<5>
                         >;

    static_assert(
            is_same<
                    TL<int_c_t<0>, int_c_t<1>, int_c_t<3>, int_c_t<6>, int_c_t<10>, int_c_t<15>>,
                    sum_list_0_t
            >(),
            ""
    );

    // (((((0 + 1) + 2) + 3) + 4) + 5) = 15
    using sum_list_1_t = FoldListT<
                            Plus,
                            int_c_t<0>,  // init
                            TL<
                                    int_c_t<1>,
                                    int_c_t<2>,
                                    int_c_t<3>,
                                    int_c_t<4>,
                                    int_c_t<5>
                            >
                         >;

    static_assert(
            is_same<
                    TL<int_c_t<0>, int_c_t<1>, int_c_t<3>, int_c_t<6>, int_c_t<10>, int_c_t<15>>,
                    sum_list_1_t
            >(),
            ""
    );
}

