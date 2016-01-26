#include "../catch.hpp"

#include "rocky/base/TypeSelection.h"


TEST_CASE("Selecting type on compile time bool condition", "[TypeSelection]")
{
    using std::is_same;

    struct A { };
    struct B { };
    struct C { using type = int; };

    static_assert(is_same<typename SelectTypeIf<true, A, B>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<false, A, B>::type, B>(), "B should be selected.");

    static_assert(is_same<typename SelectTypeIf<true, A, C>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<false, A, C>::type, int>(), "int should be selected.");

    static_assert(is_same<typename std::conditional_t<true, A, B>, A>(), "A should be selected.");
    static_assert(is_same<typename std::conditional_t<false, A, B>, B>(), "B should be selected.");

    static_assert(is_same<typename std::conditional_t<true, A, C>, A>(), "A should be selected.");
    static_assert(is_same<typename std::conditional_t<false, A, C>, C>(), "C should be selected.");
}

