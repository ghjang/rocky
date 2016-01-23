#include "../catch.hpp"

#include "rocky/skull/Zip.h"

#include "rocky/meta/IntegralConstantUtility.h"


TEST_CASE("Zip", "[skull]")
{
    using std::is_same;
    using std::tuple;
    using std::pair;

    static_assert(is_same<TypeList<>, ZipT<TypeList<>, TypeList<>>>(), "");
    static_assert(is_same<TypeList<>, ZipT<TypeList<char>, TypeList<>>>(), "");
    static_assert(is_same<TypeList<>, ZipT<TypeList<>, TypeList<char>>>(), "");

    static_assert(
            is_same<
                    TypeList<pair<char, int_c_t<0>>>,
                    ZipT<TypeList<char, int>, TypeList<int_c_t<0>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<pair<char, int_c_t<0>>>,
                    ZipT<TypeList<char>, TypeList<int_c_t<0>, int_c_t<1>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<
                            pair<char, int_c_t<0>>,
                            pair<int, int_c_t<1>>,
                            pair<float, int_c_t<2>>,
                            pair<double, int_c_t<3>>
                    >,
                    ZipT<TypeList<char, int, float, double>, TypeList<int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>>>
            >(),
            ""
    );

    static_assert(is_same<tuple<>, ZipT<tuple<>, tuple<>>>(), "");
    static_assert(is_same<tuple<>, ZipT<tuple<char>, tuple<>>>(), "");
    static_assert(is_same<tuple<>, ZipT<tuple<>, tuple<char>>>(), "");
}

