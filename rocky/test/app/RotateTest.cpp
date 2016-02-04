#include "../catch.hpp"

#include "rocky/app/Rotate.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Rotate", "[Rotate]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TL<>, RotateT<int_c_t<-1>>>(), "");
    static_assert(is_same<TL<>, RotateT<int_c_t<0>>>(), "");
    static_assert(is_same<TL<>, RotateT<int_c_t<1>>>(), "");

    static_assert(
            is_same<
                    TL<char, int, int64_t, float, double>,
                    RotateT<int_c_t<0>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int, int64_t, float, double, char>,
                    RotateT<int_c_t<-1>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<double, char, int, int64_t, float>,
                    RotateT<int_c_t<1>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<float, double, char, int, int64_t>,
                    RotateT<int_c_t<-3>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int64_t, float, double, char, int>,
                    RotateT<int_c_t<3>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, int64_t, float, double>,
                    RotateT<int_c_t<-5>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, int64_t, float, double>,
                    RotateT<int_c_t<5>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<int64_t, float, double, char, int>,
                    RotateT<int_c_t<-7>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<float, double, char, int, int64_t>,
                    RotateT<int_c_t<7>, char, int, int64_t, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<float, double, char, int, int64_t>,
                    RotateT<int_c_t<7>, TL<char, int, int64_t, float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<float, double, char, int, int64_t>,
                    RotateT<int_c_t<7>, tuple<char, int, int64_t, float, double>>
            >(),
            ""
    );
}

