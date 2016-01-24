#include "../catch.hpp"

#include "rocky/meta/Find.h"


TEST_CASE("find element type", "[Find]")
{
    using std::is_same;

    static_assert(-1 == Find<int>(), "doesn't have 'int' type.");
    static_assert(-1 == Find<int, char, char, char, char, char>(), "doesn't have 'int' type.");
    static_assert(0 == Find<int, int, char, char, char, char>(), "'int' type at '0'.");
    static_assert(4 == Find<int, char, char, char, char, int>(), "'int' type at '4'.");
    static_assert(2 == Find<int, char, char, int, char, char>(), "'int' type at '2'.");
    static_assert(
            1 == Find<
                    int,
                    char, int, char, int, char, char, char
                 >(),
            "the first 'int' type at '1'."
    );
}

TEST_CASE("reverse find element type", "[Find]")
{
    using std::is_same;

    static_assert(-1 == ReverseFind<int>(), "doesn't have 'int' type.");
    static_assert(-1 == ReverseFind<int, char, char, char, char, char>(), "doesn't have 'int' type.");
    static_assert(0 == ReverseFind<int, int, char, char, char, char>(), "'int' type at '0'.");
    static_assert(4 == ReverseFind<int, char, char, char, char, int>(), "'int' type at '4'.");
    static_assert(2 == ReverseFind<int, char, char, int, char, char>(), "'int' type at '2'.");
    static_assert(
            3 == ReverseFind<
                        int,
                        char, int, char, int, char, char, char
                    >(),
            "the last 'int' type at '3'."
    );
}

TEST_CASE("find tuple element type", "[Find]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(-1 == Find<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(-1 == Find<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(0 == Find<int, tuple_t>(), "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(4 == Find<int, tuple_t>(), "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(2 == Find<int, tuple_t>(), "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(1 == Find<int, tuple_t>(), "tuple_t has the first 'int' type at '1'.");
    }
}

TEST_CASE("reverse find tuple element type", "[Find]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(-1 == ReverseFind<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(-1 == ReverseFind<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(0 == ReverseFind<int, tuple_t>(), "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(4 == ReverseFind<int, tuple_t>(), "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(2 == ReverseFind<int, tuple_t>(), "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(1 == Find<int, tuple_t>(), "tuple_t has the last 'int' type at '1'.");
        static_assert(3 == ReverseFind<int, tuple_t>(), "tuple_t has the last 'int' type at '3'.");
    }
}

