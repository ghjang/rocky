#include "../catch.hpp"

#include "rocky/base/TypeListFlatten.h"


TEST_CASE("TypeList flatten", "[TypeListFlatten]")
{
    using std::is_same;

    static_assert(is_same<TL<>, FlattenTypeListT<TL<>, TL<>> >(), "");

    static_assert(is_same<TL<char>, FlattenTypeListT<char, TL<>>>(), "");


    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenTypeListT<TL<char, int>, TL<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenTypeListT<TL<char, int>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, float, double>,
                    FlattenTypeListT<char, TL<float, double>>
            >(),
            ""
    );

    /**
     * following is not a valid pattern matching.
     */
    /*
    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenTypeListT<char, int, TL<float, double>>
            >(),
            ""
    );
     */

    static_assert(is_same<TL<char, int>, FlattenTypeListT<TL<TL<char, int>>>>(), "");

    static_assert(
            is_same<
                    TL<char, int>,
                    FlattenTypeListT<TL<TL<TL<char, int>>>>
            >(),
            ""
    );

    // NOTE: following tests are not supported.
    /*
    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenTypeListT<TL<TL<char, int>>, TL<TL<float, double>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenTypeListT<TL<TL<char, int>>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<char, float, double>,
                    FlattenTypeListT<char, TL<TL<float, double>>>
            >(),
            ""
    );
     */
}

