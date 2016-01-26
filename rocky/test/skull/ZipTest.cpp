#include "../catch.hpp"

#include "rocky/skull/Zip.h"

#include "rocky/base/IntegralConstantUtility.h"


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
                    TypeList<TypeList<char, int_c_t<0>>>,
                    ZipT<TypeList<char, int>, TypeList<int_c_t<0>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<TypeList<char, int_c_t<0>>>,
                    ZipT<TypeList<char>, TypeList<int_c_t<0>, int_c_t<1>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<
                            TypeList<char, int_c_t<0>>,
                            TypeList<int, int_c_t<1>>,
                            TypeList<float, int_c_t<2>>,
                            TypeList<double, int_c_t<3>>
                    >,
                    ZipT<TypeList<char, int, float, double>, TypeList<int_c_t<0>, int_c_t<1>, int_c_t<2>, int_c_t<3>>>
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

