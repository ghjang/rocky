#include "../catch.hpp"

#include "rocky/base/TypeList.h"


TEST_CASE("TypeListSize", "[TypeList]")
{
    static_assert(0 == TypeListSize<>(), "");
    static_assert(1 == TypeListSize<int>(), "");
    static_assert(3 == TypeListSize<char, int, float>(), "");

    static_assert(0 == TypeListSize<TypeList<>>(), "");
    static_assert(1 == TypeListSize<TypeList<int>>(), "");
    static_assert(3 == TypeListSize<TypeList<char, int, float>>(), "");
}

TEST_CASE("ToTuple", "[TypeList]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<tuple<>, ToTupleT<TypeList<>>>(), "");
    static_assert(is_same<tuple<char, int>, ToTupleT<TypeList<char, int>>>(), "");
    static_assert(!is_same<TypeList<char, int>, ToTupleT<TypeList<char, int>>>(), "");
}

TEST_CASE("ToTypeList", "[TypeList]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TypeList<>, ToTypeListT<tuple<>>>(), "");
    static_assert(is_same<TypeList<char, int>, ToTypeListT<tuple<char, int>>>(), "");
    static_assert(!is_same<tuple<char, int>, ToTypeListT<tuple<char, int>>>(), "");
}

