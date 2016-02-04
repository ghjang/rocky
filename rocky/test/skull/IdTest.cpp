#include "../catch.hpp"

#include "rocky/skull/Id.h"


TEST_CASE("Id", "[skull]")
{
    using std::is_same;
    static_assert(is_same<char, IdT<char>>(), "");
    static_assert(!is_same<char, IdT<int>>(), "");
}
