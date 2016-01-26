#include "../catch.hpp"

#include "rocky/base/TypeListJoin.h"


TEST_CASE("TypeListJoin", "[TypeListJoin]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TypeList<TypeList<>, TypeList<>>, JoinTypeListT<TypeList<>, TypeList<>>>(), "");
    static_assert(is_same<TypeList<TypeList<char>, TypeList<>>, JoinTypeListT<TypeList<char>, TypeList<>>>(), "");
    static_assert(is_same<TypeList<TypeList<>, TypeList<char>>, JoinTypeListT<TypeList<>, TypeList<char>>>(), "");
    static_assert(
            is_same<TypeList<TypeList<char>, TypeList<char>>, JoinTypeListT<TypeList<char>, TypeList<char>>>(),
            ""
    );

    static_assert(
            is_same<TypeList<TypeList<char>, char, int>, JoinTypeListT<TypeList<char>, char, int>>(),
            ""
    );
    static_assert(
            is_same<TypeList<char, TypeList<char, int>>, JoinTypeListT<char, TypeList<char, int>>>(),
            ""
    );
}

TEST_CASE("TypeList operator +", "[TypeListJoin]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TypeList<TypeList<char, int>, TypeList<float, double>>>(), "");

    auto rt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decltype(rt), TypeList<TypeList<char, int>, TypeList<float, double>>>(), "");
}

