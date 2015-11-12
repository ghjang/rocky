#include "catch.hpp"

#include "rocky/ReverseTuple.h"


TEST_CASE("Reversing tuple's template parameters", "[ReverseTuple]")
{
    using std::is_same;
    using std::tuple;

    using T = tuple<char, short, int, float, double>;
    using ReversedT = tuple<double, float, int, short, char>;
    static_assert(is_same<typename ReverseTuple<T>::type, ReversedT>::value, "ReverseTuple<T>::type should be ReversedT.");
}

