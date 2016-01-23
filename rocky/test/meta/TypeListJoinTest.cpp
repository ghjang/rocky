#include "../catch.hpp"

#include "rocky/meta/TypeListJoin.h"

#include <type_traits>


TEST_CASE("TypeList join", "[TypeListUtility]")
{
    using std::is_same;

    static_assert(is_same<TypeList<>, JoinTypeListT<TypeList<>, TypeList<>> >(), "");

    static_assert(is_same<TypeList<char>, JoinTypeListT<char, TypeList<>>>(), "");


    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    JoinTypeListT<TypeList<char, int>, TypeList<float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    JoinTypeListT<TypeList<char, int>, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, float, double>,
                    JoinTypeListT<char, TypeList<float, double>>
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
                    JoinTypeListT<char, int, TypeList<float, double>>
            >(),
            ""
    );
     */
}

TEST_CASE("TypeList operator +", "[TypeListUtility]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TypeList<char, int, float, double>>(), "");

    auto rt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decltype(rt), TypeList<char, int, float, double>>(), "");
}


