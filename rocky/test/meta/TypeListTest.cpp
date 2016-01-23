#include "../catch.hpp"

#include "rocky/meta/TypeList.h"

#include <type_traits>


TEST_CASE("TypeListSize", "[TypeList]")
{
    static_assert(0 == TypeListSize<>(), "");
    static_assert(1 == TypeListSize<int>(), "");
    static_assert(3 == TypeListSize<char, int, float>(), "");

    static_assert(0 == TypeListSize<TypeList<>>(), "");
    static_assert(1 == TypeListSize<TypeList<int>>(), "");
    static_assert(3 == TypeListSize<TypeList<char, int, float>>(), "");
}

TEST_CASE("TypeList join", "[TypeList]")
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

TEST_CASE("TypeList operator +", "[TypeList]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TypeList<char, int, float, double>>(), "");

    auto rt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decltype(rt), TypeList<char, int, float, double>>(), "");
}

TEST_CASE("TypeListToTuple", "[TypeList]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<tuple<>, TypeListToTupleT<TypeList<>>>(), "");
    static_assert(is_same<tuple<char, int>, TypeListToTupleT<TypeList<char, int>>>(), "");
    static_assert(!is_same<TypeList<char, int>, TypeListToTupleT<TypeList<char, int>>>(), "");
}

