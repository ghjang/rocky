#include "../catch.hpp"

#include "rocky/skull/Zip.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Zip", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TL<>, ZipT<TL<>, TL<>>>(), "");
    static_assert(is_same<TL<>, ZipT<TL<char>, TL<>>>(), "");
    static_assert(is_same<TL<>, ZipT<TL<>, TL<char>>>(), "");

    static_assert(
            is_same<
                    TL<TL<char, int_c_t<0>>>,
                    ZipT<TL<char, int>, TL<int_c_t<0>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<TL<char, int_c_t<0>>>,
                    ZipT<TL<char>, TL<int_c_t<0>, int_c_t<1>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<
                            TL<char, int_c_t<0>>,
                            TL<int, int_c_t<1>>,
                            TL<float, int_c_t<2>>,
                            TL<double, int_c_t<3>>
                    >,
                    ZipT<TL<char, int, float, double>, TL<int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>>>
            >(),
            ""
    );

    static_assert(is_same<tuple<>, ZipT<tuple<>, tuple<>>>(), "");
    static_assert(is_same<tuple<>, ZipT<tuple<char>, tuple<>>>(), "");
    static_assert(is_same<tuple<>, ZipT<tuple<>, tuple<char>>>(), "");

    static_assert(
            is_same<
                    tuple<tuple<char, int_c_t<0>>>,
                    ZipT<tuple<char, int>, tuple<int_c_t<0>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<tuple<char, int_c_t<0>>>,
                    ZipT<tuple<char>, tuple<int_c_t<0>, int_c_t<1>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<
                            tuple<char, int_c_t<0>>,
                            tuple<int, int_c_t<1>>,
                            tuple<float, int_c_t<2>>,
                            tuple<double, int_c_t<3>>
                    >,
                    ZipT<tuple<char, int, float, double>, tuple<int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>>>
            >(),
            ""
    );
}

