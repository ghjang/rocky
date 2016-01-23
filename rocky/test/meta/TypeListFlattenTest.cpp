#include "../catch.hpp"

#include "rocky/meta/TypeListFlatten.h"


TEST_CASE("TypeList flatten", "[TypeListFlatten]")
{
    using std::is_same;

    static_assert(is_same<TypeList<>, FlattenTypeListT<TypeList<>, TypeList<>> >(), "");

    static_assert(is_same<TypeList<char>, FlattenTypeListT<char, TypeList<>>>(), "");


    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    FlattenTypeListT<TypeList<char, int>, TypeList<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    FlattenTypeListT<TypeList<char, int>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, float, double>,
                    FlattenTypeListT<char, TypeList<float, double>>
            >(),
            ""
    );

    /**
     * following is not a valid pattern matching.
     */
    /*
    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    FlattenTypeListT<char, int, TypeList<float, double>>
            >(),
            ""
    );
     */

    static_assert(is_same<TypeList<char, int>, FlattenTypeListT<TypeList<TypeList<char, int>>>>(), "");

    static_assert(
            is_same<
                    TypeList<char, int>,
                    FlattenTypeListT<TypeList<TypeList<TypeList<char, int>>>>
            >(),
            ""
    );

    // NOTE: following tests are not supported.
    /*
    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    FlattenTypeListT<TypeList<TypeList<char, int>>, TypeList<TypeList<float, double>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    FlattenTypeListT<TypeList<TypeList<char, int>>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, float, double>,
                    FlattenTypeListT<char, TypeList<TypeList<float, double>>>
            >(),
            ""
    );
     */
}

