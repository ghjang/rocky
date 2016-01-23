#include "../catch.hpp"

#include "rocky/meta/ReverseTuple.h"


TEST_CASE("Reversing tuple's template parameters", "[ReverseTuple]")
{
    using std::is_same;
    using std::tuple;

    using T = tuple<char, short, int, float, double>;
    using ReversedT = tuple<double, float, int, short, char>;
    static_assert(
            is_same<typename ReverseElementType<T>::type, ReversedT>(),
            "ReverseElementType<T>::type should be ReversedT."
    );
}

