#include "../catch.hpp"

#include "rocky/skull/Fst.h"


TEST_CASE("Fst", "[skull]")
{
    using std::is_same;
    using std::pair;
    using std::tuple;

    // following is an expected compile error.
    //static_assert(is_same<char, FstT<>>());
    //static_assert(is_same<char, FstT<char, int, float>>());
    //static_assert(is_same<char, FstT<TypeList<char, int, float>>>());
    //static_assert(is_same<char, FstT<tuple<char, int, float>>>());

    static_assert(is_same<char, FstT<char, int>>());
    static_assert(is_same<char, FstT<TypeList<char, int>>>());
    static_assert(is_same<char, FstT<pair<char, int>>>());
    static_assert(is_same<char, FstT<tuple<char, int>>>());

    static_assert(is_same<TypeList<char, int>, FstT<TypeList<char, int>, float>>());
}

