#include "../catch.hpp"

#include "rocky/skull/Drop.h"


TEST_CASE("Drop", "[skull]")
{
    using std::is_same;
    using std::tuple;

    //
    static_assert(is_same<TypeList<>, DropT<0>>(), "");
    static_assert(is_same<TypeList<>, DropT<0, TypeList<>>>(), "");

    //
    static_assert(is_same<TypeList<char, int, float, double>, DropT<0, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<int, float, double>, DropT<1, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<float, double>, DropT<2, char, int, float, double>>(), "");
    static_assert(is_same<TypeList<>, DropT<5, char, int, float, double>>(), "");

    //
    static_assert(is_same<TypeList<char, int, float, double>, DropT<0, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<int, float, double>, DropT<1, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<float, double>, DropT<2, TypeList<char, int, float, double>>>(), "");
    static_assert(is_same<TypeList<>, DropT<5, TypeList<char, int, float, double>>>(), "");

    //
    static_assert(is_same<tuple<char, int, float, double>, DropT<0, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<int, float, double>, DropT<1, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<float, double>, DropT<2, tuple<char, int, float, double>>>(), "");
    static_assert(is_same<tuple<>, DropT<5, tuple<char, int, float, double>>>(), "");
}

