#include "../catch.hpp"

#include "rocky/skull/Null.h"

#include "rocky/base/TypeList.h"


TEST_CASE("Null", "[skull]")
{
    using std::tuple;

    static_assert(Null<>(), "");
    static_assert(Null<TypeList<>>(), "");
    static_assert(Null<tuple<>>(), "");

    static_assert(!Null<int>(), "");
    static_assert(!Null<TypeList<int>>(), "");
    static_assert(!Null<tuple<int>>(), "");
}

