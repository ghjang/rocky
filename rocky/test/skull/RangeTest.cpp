#include "../catch.hpp"

#include "rocky/skull/Range.h"


TEST_CASE("Range for two integers", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    RangeT<int_c_t<1>, int_c_t<5>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    MakeRangeT<1, 5>
            >(),
            ""
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 2, 3, 4, 5>,
                    IntConstListToIntSeqT<RangeT<int_c_t<1>, int_c_t<5>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 2, 3, 4, 5>,
                    MakeRangeSequenceT<1, 5>
            >(),
            ""
    );
}

TEST_CASE("Range for two characters", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<char_c_t<'a'>, char_c_t<'b'>, char_c_t<'c'>, char_c_t<'d'>, char_c_t<'e'>>,
                    MakeCharRangeT<'a', 'e'>
            >(),
            ""
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'a', 'b', 'c', 'd', 'e'>,
                    MakeCharRangeSequenceT<'a', 'e'>
            >(),
            ""
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'A', 'B', 'C', 'D', 'E'>,
                    MakeCharRangeSequenceT<'A', 'E'>
            >(),
            ""
    );
}

