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
            >()
    );

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<2>, int_c_t<3>, int_c_t<4>, int_c_t<5>>,
                    MakeRangeT<1, 5>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 2, 3, 4, 5>,
                    IntConstListToIntSeqT<RangeT<int_c_t<1>, int_c_t<5>>>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 2, 3, 4, 5>,
                    MakeRangeSequenceT<1, 5>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5>,
                    MakeRangeSequenceT<-5, 5>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 10>,
                    MakeRangeSequenceT<10, 10>
            >()
    );
}

TEST_CASE("Stepped range for two integers", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<3>, int_c_t<5>, int_c_t<7>, int_c_t<9>>,
                    RangeT<int_c_t<1>, int_c_t<3>, int_c_t<10>>
            >()
    );

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<3>, int_c_t<5>, int_c_t<7>, int_c_t<9>>,
                    MakeSteppedRangeT<1, 3, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3, 5, 7, 9>,
                    IntConstListToIntSeqT<RangeT<int_c_t<1>, int_c_t<3>, int_c_t<10>>>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3, 5, 7, 9>,
                    MakeSteppedRangeSequenceT<1, 3, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, -5, -3, -1, 1, 3, 5>,
                    MakeSteppedRangeSequenceT<-5, -3, 5>
            >()
    );

    // NOTE: following is an expected compile time error.
    /*
    static_assert(
            is_same<
                    integer_sequence<int, 10, 11, 12, 13, 14, 15>,
                    MakeSteppedRangeSequenceT<10, 10, 15>
            >()
    );
     */
}

TEST_CASE("Range for two characters", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<char_c_t<'a'>, char_c_t<'b'>, char_c_t<'c'>, char_c_t<'d'>, char_c_t<'e'>>,
                    MakeCharRangeT<'a', 'e'>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'a', 'b', 'c', 'd', 'e'>,
                    MakeCharRangeSequenceT<'a', 'e'>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'A', 'B', 'C', 'D', 'E'>,
                    MakeCharRangeSequenceT<'A', 'E'>
            >()
    );
}

TEST_CASE("Stepped range for two characters", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<
                            char_c_t<'a'>,
                            char_c_t<'e'>,
                            char_c_t<'i'>,
                            char_c_t<'m'>,
                            char_c_t<'q'>,
                            char_c_t<'u'>,
                            char_c_t<'y'>
                    >,
                    MakeSteppedCharRangeT<'a', 'e', 'z'>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'a', 'e', 'i', 'm', 'q', 'u', 'y'>,
                    MakeSteppedCharRangeSequenceT<'a', 'e', 'z'>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<char, 'A', 'E', 'I', 'M', 'Q', 'U', 'Y'>,
                    MakeSteppedCharRangeSequenceT<'A', 'E', 'Z'>
            >()
    );
}

TEST_CASE("Even range for two integers", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    integer_sequence<int, 0, 2, 4, 6, 8, 10>,
                    MakeEvenRangeSequenceT<0, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 2, 4, 6, 8, 10>,
                    MakeEvenRangeSequenceT<1, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 2, 4, 6, 8, 10>,
                    MakeEvenRangeSequenceT<1, 11>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 2>,
                    MakeEvenRangeSequenceT<1, 3>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 2>,
                    MakeEvenRangeSequenceT<1, 2>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 2>,
                    MakeEvenRangeSequenceT<2, 2>
            >()
    );

    /**
     * NOTE: following is an expected compile-time error. can't make even range for (1, 1).
     */
    /*
    static_assert(
            is_same<
                    integer_sequence<int>,
                    MakeEvenRangeSequenceT<1, 1>
            >()
    );
     */
}

TEST_CASE("Odd range for two integers", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3, 5, 7, 9>,
                    MakeOddRangeSequenceT<0, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3, 5, 7, 9>,
                    MakeOddRangeSequenceT<1, 10>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3, 5, 7, 9, 11>,
                    MakeOddRangeSequenceT<1, 11>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1, 3>,
                    MakeOddRangeSequenceT<1, 3>
            >()
    );

    static_assert(
            is_same<
                    integer_sequence<int, 1>,
                    MakeOddRangeSequenceT<1, 2>
            >()
    );

    /**
     * NOTE: following is an expected compile-time error. can't make even range for (1, 1).
     */
    /*
    static_assert(
            is_same<
                    integer_sequence<int, 2>,
                    MakeOddRangeSequenceT<2, 2>
            >()
    );
     */

    static_assert(
            is_same<
                    integer_sequence<int, 1>,
                    MakeOddRangeSequenceT<1, 1>
            >()
    );
}

