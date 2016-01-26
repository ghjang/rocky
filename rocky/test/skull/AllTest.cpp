#include "../catch.hpp"

#include "rocky/skull/All.h"


TEST_CASE("All", "[skull]")
{
    using std::is_same;
    using std::is_pointer;
    using std::tuple;

    static_assert(All<is_pointer>(), "");

    static_assert(All<is_pointer, char *, int *, float *, double *>(), "");
    static_assert(!All<is_pointer, char *, int *, float, double *>(), "");

    static_assert(All<is_pointer, TypeList<char *, int *, float *, double *>>(), "");
    static_assert(!All<is_pointer, TypeList<char *, int *, float, double *>>(), "");

    static_assert(All<is_pointer, tuple<char *, int *, float *, double *>>(), "");
    static_assert(!All<is_pointer, tuple<char *, int *, float, double *>>(), "");
}

