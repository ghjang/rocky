#include "catch.hpp"

#include "rocky/meta/TypeUtility.h"

#include <type_traits>


TEST_CASE("basic type wrapping as a value", "[TypeUtility]")
{
    using std::is_same;

    static_assert(is_same<Identity<int> const, decltype(type_c<int>)>(), "Identity<int> const == decltype(type_c<int>)");
}

