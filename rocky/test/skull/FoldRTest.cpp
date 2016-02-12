#include "../catch.hpp"

#include "rocky/skull/FoldR.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("fold right, integral constant sum", "[Fold]")
{
    using sum_t = FoldRT<
                        Quote<Plus>,
                        int_c_t<0>,  // init
                        int_c_t<1>,
                        int_c_t<2>,
                        int_c_t<3>,
                        int_c_t<4>,
                        int_c_t<5>
                  >;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant subtract", "[Fold]")
{
    using subtract_t = FoldRT<
                            Quote<Minus>,
                            int_c_t<0>,  // init
                            int_c_t<1>,
                            int_c_t<2>,
                            int_c_t<3>,
                            int_c_t<4>,
                            int_c_t<5>
                       >;
    static_assert(subtract_t() == 3, "(1 - (2 - (3 - (4 - (5 - 0))))) = 3");
}

TEST_CASE("fold right, integral constant in tuple sum", "[Fold]")
{
    using std::tuple;

    using integral_tuple_t = tuple<
                                int_c_t<1>,
                                int_c_t<2>,
                                int_c_t<3>,
                                int_c_t<4>,
                                int_c_t<5>
                             >;

    using sum_t = FoldRWithUnpackT<
                        Quote<Plus>,
                        int_c_t<0>,  // init
                        integral_tuple_t
                  >;
    static_assert(sum_t() == 15, "1 + (2 + (3 + (4 + (5 + 0)))) = 15");
}

TEST_CASE("fold right, integral constant multiply", "[Fold]")
{
    using mul_t = FoldRT<
                        Quote<Multiply>,
                        int_c_t<1>,  // init
                        int_c_t<1>,
                        int_c_t<2>,
                        int_c_t<3>,
                        int_c_t<4>,
                        int_c_t<5>
                  >;
    static_assert(mul_t() == 120, "1 * (2 * (3 * (4 * (5 * 1)))) = 120");
}

