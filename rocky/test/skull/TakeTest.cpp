#include "../catch.hpp"

#include "rocky/skull/Take.h"


TEST_CASE("Take", "[skull]")
{
    using std::is_same;
    using std::tuple;

    //
    static_assert(is_same<TypeList<>, TakeT<0>>(), "");
    static_assert(is_same<TypeList<>, TakeT<0, TypeList<>>>(), "");

    //
    static_assert(is_same<TypeList<>, TakeT<0, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<char>, TakeT<1, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<char, int>, TakeT<2, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<char, int, float, double>, TakeT<5, char, int, float, double>>(), "");

    //
    static_assert(is_same<TypeList<>, TakeT<0, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<char>, TakeT<1, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<char, int>, TakeT<2, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<char, int, float, double>, TakeT<5, TypeList<char, int, float, double>>>(), "");

    //
    static_assert(is_same<tuple<>, TakeT<0, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<char>, TakeT<1, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<char, int>, TakeT<2, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<char, int, float, double>, TakeT<5, tuple<char, int, float, double>>>(), "");
}

