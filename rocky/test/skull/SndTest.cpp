#include "../catch.hpp"

#include "rocky/skull/Snd.h"


TEST_CASE("Snd", "[skull]")
{
    using std::is_same;
    using std::pair;
    using std::tuple;

    // following is an expected compile error.
    //static_assert(is_same<char, SndT<>>(), "");
    //static_assert(is_same<char, SndT<char, int, float>>(), "");
    //static_assert(is_same<char, SndT<TypeList<char, int, float>>>(), "");
    //static_assert(is_same<char, SndT<tuple<char, int, float>>>(), "");

    static_assert(is_same<int, SndT<char, int>>(), "");
    static_assert(is_same<int, SndT<TypeList<char, int>>>(), "");
    static_assert(is_same<int, SndT<pair<char, int>>>(), "");
    static_assert(is_same<int, SndT<tuple<char, int>>>(), "");

    static_assert(is_same<float, SndT<TypeList<char, int>, float>>(), "");
}

