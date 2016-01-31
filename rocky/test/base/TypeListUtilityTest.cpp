#include "../catch.hpp"

#include "rocky/base/TypeListUtility.h"


TEST_CASE("HasSameType", "[TypeListUtility]")
{
    using std::pair;
    using std::tuple;

    static_assert(HasSameType<>(), "");
    static_assert(HasSameType<TypeList<>>(), "");
    static_assert(HasSameType<tuple<>>(), "");

    static_assert(HasSameType<char, char, char>(), "");
    static_assert(!HasSameType<char, wchar_t, char>(), "");

    static_assert(HasSameType<TypeList<char, char, char>>(), "");
    static_assert(!HasSameType<TypeList<char, wchar_t, char>>(), "");

    static_assert(HasSameType<pair<char, char>>(), "");
    static_assert(!HasSameType<pair<char, wchar_t>>(), "");

    static_assert(HasSameType<tuple<char, char, char>>(), "");
    static_assert(!HasSameType<tuple<char, wchar_t, char>>(), "");
}

