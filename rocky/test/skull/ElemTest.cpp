#include "../catch.hpp"

#include "rocky/skull/Elem.h"


TEST_CASE("Elem with null type list", "[skull]")
{
    static_assert(!Elem<int>(), "");
    static_assert(!Elem<int, TypeList<>>(), "");
    static_assert(!Elem<int, std::tuple<>>(), "");
}

TEST_CASE("Elem", "[skull]")
{
    static_assert(!Elem<int>(), "doesn't have 'int' type.");
    static_assert(!Elem<int, char, char, char, char, char>(), "doesn't have 'int' type.");
    static_assert(Elem<int, int, char, char, char, char>(), "'int' type at '0'.");
    static_assert(Elem<int, char, char, char, char, int>(), "'int' type at '4'.");
    static_assert(Elem<int, char, char, int, char, char>(), "'int' type at '2'.");
    static_assert(
            Elem<
                    int,
                    char, int, char, int, char, char, char
            >(),
            "the last 'int' type at '3'."
    );
}

TEST_CASE("Elem with tuple", "[skull]")
{
    using std::is_same;
    using std::tuple;

    {
        using tuple_t = tuple<>;
        static_assert(!Elem<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<char, char, char, char, char>;
        static_assert(!Elem<int, tuple_t>(), "tuple_t doesn't have 'int' type.");
    }

    {
        using tuple_t = tuple<int, char, char, char, char>;
        static_assert(Elem<int, tuple_t>(), "tuple_t has 'int' type at '0'.");
    }

    {
        using tuple_t = tuple<char, char, char, char, int>;
        static_assert(Elem<int, tuple_t>(), "tuple_t has 'int' type at '4'.");
    }

    {
        using tuple_t = tuple<char, char, int, char, char>;
        static_assert(Elem<int, tuple_t>(), "tuple_t has 'int' type at '2'.");
    }

    {
        using tuple_t = tuple<char, int, char, int, char, char, char>;
        static_assert(Elem<int, tuple_t>(), "tuple_t has the last 'int' type at '3'.");
    }
}

TEST_CASE("Elem with TypeList", "[skull]")
{
    static_assert(Elem<int, TypeList<char, int, char, int, char, char, char>>(), "");
}

