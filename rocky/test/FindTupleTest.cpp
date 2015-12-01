#include "catch.hpp"

#include "rocky/meta/FindTuple.h"


TEST_CASE("find tuple element type", "[FindTuple]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(-1 == FindElementType<tuple_t, int>::value, "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(0 == FindElementType<tuple_t, int>::value, "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(4 == FindElementType<tuple_t, int>::value, "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(2 == FindElementType<tuple_t, int>::value, "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(1 == FindElementType<tuple_t, int>::value, "tuple_t has the first 'int' type at '1'.");
    }
}


