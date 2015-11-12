#include "catch.hpp"

#include "rocky/TypeSelection.h"


TEST_CASE("Selecting type on compile time bool condition", "[TypeSelection]")
{
    using std::is_same;

    struct A { };
    struct B { };
    struct C { using type = int; };

    static_assert(is_same<typename SelectTypeIf<std::true_type, A, B>::type, A>::value, "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<std::false_type, A, B>::type, B>::value, "B should be selected.");

    static_assert(is_same<typename SelectTypeIf<std::true_type, A, C>::type, A>::value, "A should be selected.");
    static_assert(is_same<typename SelectTypeIf<std::false_type, A, C>::type, int>::value, "int should be selected.");

    static_assert(is_same<typename SelectParameterTypeIf<std::true_type, A, B>::type, A>::value, "A should be selected.");
    static_assert(is_same<typename SelectParameterTypeIf<std::false_type, A, B>::type, B>::value, "B should be selected.");

    static_assert(is_same<typename SelectParameterTypeIf<std::true_type, A, C>::type, A>::value, "A should be selected.");
    static_assert(is_same<typename SelectParameterTypeIf<std::false_type, A, C>::type, C>::value, "C should be selected.");
}

