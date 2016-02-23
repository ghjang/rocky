#include "../catch.hpp"

#include "rocky/base/TypeListFlatten.h"


TEST_CASE("TypeList flatten", "[TypeListFlattenAs]")
{
    using std::is_same;

    static_assert(is_same<TL<>, FlattenAsTypeListT<>>(), "");
    static_assert(is_same<TL<>, FlattenAsTypeListT<TL<>>>(), "");
    static_assert(is_same<TL<>, FlattenAsTypeListT<TL<>, TL<>> >(), "");

    static_assert(is_same<TL<char>, FlattenAsTypeListT<char, TL<>>>(), "");


    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenAsTypeListT<TL<char, int>, TL<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenAsTypeListT<TL<char, int>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, float, double>,
                    FlattenAsTypeListT<char, TL<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenAsTypeListT<char, int, TL<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<long, char, int, float, double>,
                    FlattenAsTypeListT<TL<long>, char, int, TL<float, double>>
            >(),
            ""
    );

    static_assert(is_same<TL<char, int>, FlattenAsTypeListT<TL<TL<char, int>>>>(), "");

    static_assert(
            is_same<
                    TL<char, int>,
                    FlattenAsTypeListT<TL<TL<TL<char, int>>>>
            >(),
            ""
    );

    // NOTE: following tests are not supported.
    /*
    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenAsTypeListT<TL<TL<char, int>>, TL<TL<float, double>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenAsTypeListT<TL<TL<char, int>>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, float, double>,
                    FlattenAsTypeListT<char, TL<TL<float, double>>>
            >(),
            ""
    );
     */
}

