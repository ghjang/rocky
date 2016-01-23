#include "../catch.hpp"

#include "rocky/meta/TypeListJoin.h"


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
}

TEST_CASE("TypeList operator +", "[TypeListJoin]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TypeList<char, int, float, double>>(), "");

    auto rt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decltype(rt), TypeList<char, int, float, double>>(), "");
}

