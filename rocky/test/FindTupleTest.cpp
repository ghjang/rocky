#include "catch.hpp"

#include "rocky/meta/FindTuple.h"

TEST_CASE("find element type", "[FindTuple]")
{
    using std::is_same;

    static_assert(-1 == FindElementType<int>::value, "doesn't have 'int' type.");
    static_assert(-1 == FindElementType<int, char, char, char, char, char>::value, "doesn't have 'int' type.");
    static_assert(0 == FindElementType<int, int, char, char, char, char>::value, "'int' type at '0'.");
    static_assert(4 == FindElementType<int, char, char, char, char, int>::value, "'int' type at '4'.");
    static_assert(2 == FindElementType<int, char, char, int, char, char>::value, "'int' type at '2'.");
    static_assert(
            1 == FindElementType<
                        int,
                        char, int, char, int, char, char, char
                    >::value,
            "the first 'int' type at '1'."
    );
}

TEST_CASE("reverse find element type", "[FindTuple]")
{
    using std::is_same;

    static_assert(-1 == ReverseFindElementType<int>::value, "doesn't have 'int' type.");
    static_assert(-1 == ReverseFindElementType<int, char, char, char, char, char>::value, "doesn't have 'int' type.");
    static_assert(0 == ReverseFindElementType<int, int, char, char, char, char>::value, "'int' type at '0'.");
    static_assert(4 == ReverseFindElementType<int, char, char, char, char, int>::value, "'int' type at '4'.");
    static_assert(2 == ReverseFindElementType<int, char, char, int, char, char>::value, "'int' type at '2'.");
    static_assert(
            3 == ReverseFindElementType<
                        int,
                        char, int, char, int, char, char, char
                    >::value,
            "the last 'int' type at '3'."
    );
}

TEST_CASE("find tuple element type", "[FindTuple]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(-1 == FindElementType<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(-1 == FindElementType<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(0 == FindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(4 == FindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(2 == FindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(1 == FindElementType<int, tuple_t>::value, "tuple_t has the first 'int' type at '1'.");
    }
}

TEST_CASE("reverse find tuple element type", "[FindTuple]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(-1 == ReverseFindElementType<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(-1 == ReverseFindElementType<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(0 == ReverseFindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(4 == ReverseFindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(2 == ReverseFindElementType<int, tuple_t>::value, "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(1 == FindElementType<int, tuple_t>::value, "tuple_t has the last 'int' type at '1'.");
        static_assert(3 == ReverseFindElementType<int, tuple_t>::value, "tuple_t has the last 'int' type at '3'.");
    }
}

TEST_CASE("IsOneOf", "[FindTuple]")
{
    static_assert(!IsOneOf<int>::value, "doesn't have 'int' type.");
    static_assert(!IsOneOf<int, char, char, char, char, char>::value, "doesn't have 'int' type.");
    static_assert(IsOneOf<int, int, char, char, char, char>::value, "'int' type at '0'.");
    static_assert(IsOneOf<int, char, char, char, char, int>::value, "'int' type at '4'.");
    static_assert(IsOneOf<int, char, char, int, char, char>::value, "'int' type at '2'.");
    static_assert(
            IsOneOf<
                    int,
                    char, int, char, int, char, char, char
            >::value,
            "the last 'int' type at '3'."
    );
}

TEST_CASE("IsOneOf with tuple", "[FindTuple]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(!IsOneOf<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(!IsOneOf<int, tuple_t>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(IsOneOf<int, tuple_t>::value, "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(IsOneOf<int, tuple_t>::value, "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(IsOneOf<int, tuple_t>::value, "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(IsOneOf<int, tuple_t>::value, "tuple_t has the last 'int' type at '3'.");
    }
}

