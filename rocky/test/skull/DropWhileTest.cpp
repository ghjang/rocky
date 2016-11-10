#include "../catch.hpp"

#include "rocky/skull/DropWhile.h"


TEST_CASE("DropWhile", "[skull]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;

    static_assert(is_same<TypeList<>, DropWhileT<Quote<is_integral>>>());
    static_assert(is_same<TypeList<>, DropWhileT<Quote<is_integral>, TypeList<>>>());
    static_assert(is_same<tuple<>, DropWhileT<Quote<is_integral>, tuple<>>>());

    static_assert(is_same<TypeList<>, DropWhileT<Quote<is_integral>, char, int>>());
    static_assert(is_same<TypeList<>, DropWhileT<Quote<is_integral>, TypeList<char, int>>>());
    static_assert(is_same<tuple<>, DropWhileT<Quote<is_integral>, tuple<char, int>>>());

    static_assert(is_same<TypeList<float, double>, DropWhileT<Quote<is_integral>, char, int, float, double>>());
    static_assert(is_same<TypeList<float, double>, DropWhileT<Quote<is_integral>, TypeList<char, int, float, double>>>());
    static_assert(is_same<tuple<float, double>, DropWhileT<Quote<is_integral>, tuple<char, int, float, double>>>());
}

