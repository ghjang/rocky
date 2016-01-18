#include "../catch.hpp"

#include "rocky/skull/Tail.h"

#include <type_traits>


TEST_CASE("Tail", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // empty type list. compile-time error.
    //static_assert(!is_same<TypeList<>, typename Tail<>::type>(), "");

    static_assert(is_same<TypeList<>, typename Tail<int>::type>(), "");

    static_assert(is_same<TypeList<float, double>, typename Tail<int, float, double>::type>(), "");

    static_assert(is_same<TypeList<float, double>, typename Tail<tuple<int, float, double>>::type>(), "");
}

