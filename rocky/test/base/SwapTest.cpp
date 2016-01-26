#include "../catch.hpp"

#include "rocky/meta/Swap.h"


TEST_CASE("Swap", "[meta]")
{
    using std::is_same;
    using std::pair;
    using std::tuple;

    // NOTE: followings are expected errors.

    //static_assert(is_same<TypeList<int, char>, SwapT<>>(), "");
    //static_assert(is_same<TypeList<int, char>, SwapT<char>>(), "");

    //static_assert(is_same<TypeList<int, char>, SwapT<TypeList<>>>(), "");
    //static_assert(is_same<TypeList<int, char>, SwapT<TypeList<char>>(), "");

    //static_assert(is_same<TypeList<int, char>, SwapT<tuple<>>>(), "");
    //static_assert(is_same<TypeList<int, char>, SwapT<tuple<char>>(), "");

    static_assert(is_same<TypeList<int, char>, SwapT<char, int>>(), "");
    static_assert(is_same<TypeList<int, char>, SwapT<TypeList<char, int>>>(), "");
    static_assert(is_same<pair<int, char>, SwapT<pair<char, int>>>(), "");
    static_assert(is_same<tuple<int, char>, SwapT<tuple<char, int>>>(), "");
}

