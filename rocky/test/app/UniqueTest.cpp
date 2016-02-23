#include "../catch.hpp"

#include "rocky/app/Unique.h"

#include "rocky/base/TypeListUtility.h"


TEST_CASE("Unique", "[Unique]")
{
    using std::is_same;
    using std::tuple;
    using std::tuple_size;
    using std::tuple_element_t;

    {
        using result_unique_t = ToTupleT<UniqueT<char, char, char>>;
        using unique_t = tuple<char>;

        static_assert(1 == tuple_size<result_unique_t>(), "result_unique_t's size should be 1.");
        static_assert(is_same<char, tuple_element_t<0, result_unique_t>>(), "");
        static_assert(is_same<unique_t, result_unique_t>(), "unique tuple_t should be same as result_unique_t.");
    }
}

TEST_CASE("unique pair element type", "[Unique]")
{
    using std::is_same;
    using std::pair;

    static_assert(is_same<UniqueT<pair<char, char>>, TypeList<char>>(), "");
}

TEST_CASE("unique tuple element type", "[Unique]")
{
    using std::is_same;
    using std::tuple;
    using std::tuple_size;
    using std::tuple_element_t;

    {
        using tuple_t = tuple<char, char, char>;
        using unique_t = tuple<char>;

        using result_unique_t = UniqueT<tuple_t>;

        static_assert(1 == tuple_size<result_unique_t>(), "result_unique_t's size should be 1.");
        static_assert(is_same<char, tuple_element_t<0, result_unique_t>>(), "");
        static_assert(is_same<unique_t, result_unique_t>(), "unique tuple_t should be same as result_unique_t.");
    }

    {
        using tuple_t = tuple<char, int, char>;
        using unique_t = tuple<char, int>;

        using result_unique_t = UniqueT<tuple_t>;

        static_assert(2 == tuple_size<result_unique_t>(), "result_unique_t's size should be 2.");
        static_assert(is_same<char, tuple_element_t<0, result_unique_t>>(), "result_unique_t's first type is 'char'.");
        static_assert(is_same<int, tuple_element_t<1, result_unique_t>>(), "result_unique_t's second type is 'int'.");
        static_assert(is_same<unique_t, result_unique_t>(), "unique tuple_t should be same as result_unique_t.");
    }

    {
        using tuple_t = tuple<char, int, int, float, char, char>;
        using unique_t = tuple<char, int, float>;

        using result_unique_t = UniqueT<tuple_t>;

        static_assert(3 == tuple_size<result_unique_t>(), "result_unique_t's size should be 3.");
        static_assert(is_same<char, tuple_element_t<0, result_unique_t>>(), "result_unique_t's 1st type is 'char'.");
        static_assert(is_same<int, tuple_element_t<1, result_unique_t>>(), "result_unique_t's 2nd type is 'int'.");
        static_assert(is_same<float, tuple_element_t<2, result_unique_t>>(), "result_unique_t's 3rd type is 'float'.");
        static_assert(is_same<unique_t, result_unique_t>(), "unique tuple_t should be same as result_unique_t.");
    }
}

