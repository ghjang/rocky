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

TEST_CASE("EmptyTypeListContainerOf", "[TypeListUtility]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<EmptyTypeListContainerOfT<TypeList<>>, TypeList<>>(), "");
    static_assert(is_same<EmptyTypeListContainerOfT<tuple<>>, tuple<>>(), "");

    static_assert(is_same<EmptyTypeListContainerOfT<TypeList<char, int, float, double>>, TypeList<>>(), "");
    static_assert(is_same<EmptyTypeListContainerOfT<tuple<char, int, float, double>>, tuple<>>(), "");
}

TEST_CASE("ToTuple", "[TypeListUtility]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<tuple<>, ToTupleT<TypeList<>>>(), "");
    static_assert(is_same<tuple<char, int>, ToTupleT<TypeList<char, int>>>(), "");
    static_assert(!is_same<TypeList<char, int>, ToTupleT<TypeList<char, int>>>(), "");
}

TEST_CASE("ToTypeList", "[TypeListUtility]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TypeList<>, ToTypeListT<tuple<>>>(), "");
    static_assert(is_same<TypeList<char, int>, ToTypeListT<tuple<char, int>>>(), "");
    static_assert(!is_same<tuple<char, int>, ToTypeListT<tuple<char, int>>>(), "");
}

