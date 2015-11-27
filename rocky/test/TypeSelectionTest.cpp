#include "catch.hpp"

#include "rocky/meta/TypeSelection.h"


TEST_CASE("Selecting type on compile time bool condition", "[TypeSelection]")
{
    using std::is_same;

    struct A { };
    struct B { };
    struct C { using type = int; };

    static_assert(is_same<typename SelectTypeIf<std::true_type, A, B>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<std::false_type, A, B>::type, B>(), "B should be selected.");

    static_assert(is_same<typename SelectTypeIf<std::true_type, A, C>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<std::false_type, A, C>::type, int>(), "int should be selected.");

    static_assert(is_same<typename SelectParameterTypeIf<std::true_type, A, B>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectParameterTypeIf<std::false_type, A, B>::type, B>(), "B should be selected.");

    static_assert(is_same<typename SelectParameterTypeIf<std::true_type, A, C>::type, A>(), "A should be selected.");
    static_assert(is_same<typename SelectParameterTypeIf<std::false_type, A, C>::type, C>(), "C should be selected.");
}

