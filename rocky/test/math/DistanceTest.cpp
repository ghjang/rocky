#include "../catch.hpp"

#include "rocky/math/Distance.h"


TEST_CASE("Distance", "[math]")
{
    static_assert(0 == Distance(-1, -1));
    static_assert(0 == Distance(0, 0));
    static_assert(0 == Distance(1, 1));

    static_assert(9 == Distance(1, 10));
    static_assert(9 == Distance(10, 1));

    static_assert(9 == Distance(-1, -10));
    static_assert(11 == Distance(-1, 10));
    static_assert(11 == Distance(1, -10));
}

TEST_CASE("TDistanceT", "[math]")
{
    static_assert(0 == TDistanceT<-1, -1>());
    static_assert(0 == TDistanceT<0, 0>());
    static_assert(0 == TDistanceT<1, 1>());

    static_assert(9 == TDistanceT<1, 10>());
    static_assert(9 == TDistanceT<10, 1>());

    static_assert(9 == TDistanceT<-1, -10>());
    static_assert(11 == TDistanceT<-1, 10>());
    static_assert(11 == TDistanceT<1, -10>());
}

