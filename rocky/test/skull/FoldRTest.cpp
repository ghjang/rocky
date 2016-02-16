#include "../catch.hpp"

#include "rocky/skull/FoldR.h"

#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/skull/Head.h"
#include "rocky/skull/Last.h"
#include "rocky/skull/Init.h"
#include "rocky/skull/Filter.h"


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


namespace
{
    template <typename lhs, typename rhs>
    struct ApplyImpl : ApplyT<lhs, rhs>
    { };
} // un-named namespace

TEST_CASE("TypeComposition", "[FoldR]")
{
    using std::is_same;
    using std::is_integral;

    static_assert(
            is_same<
                    int,
                    FoldRWithUnpackT<
                            Quote<::Apply>,
                            TypeList<int, char, long>,
                            TypeList<Quote<Head>>
                    >::type
            >(),
            ""
    );

    static_assert(is_same<Quote<Filter>, LastT<Quote<Head>, Quote<Filter>>>(), "");
    static_assert(
            is_same<
                    TypeList<int, char, long>,
                    typename ApplyT<
                            LastT<Quote<Head>, Quote<Filter>>, Quote<is_integral>,
                            float, double, int, char, long
                    >::type
            >(),
            ""
    );
    static_assert(is_same<TypeList<Quote<Head>>, InitT<Quote<Head>, Quote<Filter>>>(), "");

    /*
    FoldRWithTypeListUnpack<
            Quote<::Apply>,
            typename ApplyT<
                        LastT<Quote<Head>, Quote<Filter>>, Quote<is_integral>,
                        float, double, int, char, long
            >::type,
            InitT<Quote<Head>, Quote<Filter>>
    >::type()++;
     */

    /*
    FoldRWithTypeListUnpack<
            Quote<::Apply>,
            TypeList<int, char, long>,
            TypeList<Quote<Head>>
    >::type()++;
     */

    /*
    FoldR<
            Quote<::Apply>,
            TypeList<int, char, long>,
            Quote<Head>
    >::type()++;
     */

    static_assert(is_same<int, FoldR<Quote<ApplyImpl>, TypeList<int, char, long>, Quote<Head>>::type>(), "");

    /*
    ApplyT<Quote<::Apply>, Quote<Head>, TypeList<int, char, long>>::type()++;
     */

    /*
    Quote<::Apply>::template Apply<Quote<Head>, TypeList<int, char, long>>::type()++;
     */

    static_assert(is_same<int, Quote<ApplyImpl>::template Apply<Quote<Head>, TypeList<int, char, long>>::type>(), "");

    static_assert(is_same<int, ApplyT<Quote<Head>, int, char, long>::type>(), "");

    static_assert(is_same<int, ApplyT<Quote<Head>, TypeList<int, char, long>>::type>(), "");
    /*
     * compiler bug??
    static_assert(is_same<int, typename Apply<Quote<Head>, TypeList<int, char, long>>::type>(), "");
     */

    static_assert(is_same<int, typename Quote<Head>::template Apply<TypeList<int, char, long>>::type>(), "");

    static_assert(is_same<int, ApplyT<Quote<Head>, TypeList<int, char, long>>::type>(), "");
}

