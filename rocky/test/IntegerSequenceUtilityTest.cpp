#include "catch.hpp"

#include "rocky/meta/IntegerSequenceUtility.h"


TEST_CASE("join integer sequence", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using seq1_t = integer_sequence<int, 1, 2, 3>;
    using seq2_t = integer_sequence<int, 4, 5, 6>;
    using joined1_t = integer_sequence<int, 1, 2, 3, 4, 5, 6>;
    using reverse_joined_t = integer_sequence<int, 4, 5, 6, 1, 2, 3>;
    static_assert(is_same<joined1_t, typename JoinIntegerSequence<seq1_t, seq2_t>::type>(), "");
    static_assert(is_same<reverse_joined_t, typename JoinIntegerSequence<seq2_t, seq1_t>::type>(), "");

    // NOTE: following is an expected static assertion failure.
    /*
    using seq3_t = integer_sequence<uint, 1, 2, 3>;
    typename JoinIntegerSequence<seq1_t, seq3_t>::type seq;
     */

    using seq3_t = integer_sequence<int, 7, 8, 9>;
    using joined2_t = integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8, 9>;
    static_assert(is_same<joined2_t, typename JoinIntegerSequence<seq1_t, seq2_t, seq3_t>::type>(), "");
}

TEST_CASE("integer sequence length", "[IntegerSequenceUtility]")
{
    using std::integer_sequence;

    using empty_seq_t = integer_sequence<int>;
    static_assert(0 == IntegerSequenceLength<empty_seq_t>(), "");

    using seq1_t = integer_sequence<int, 1, 2, 3>;
    static_assert(3 == IntegerSequenceLength<seq1_t>(), "");
}

TEST_CASE("IntegerSequenceValue", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using seq_t = integer_sequence<int, 1, 2, 3, 4, 5, 6>;
    static_assert(IntegerSequenceValue<0, seq_t>::value == 1, "");
    static_assert(IntegerSequenceValue<5, seq_t>::value == 6, "");

    // NOTE: following are expected assertion failures.
    //static_assert(IntegerSequenceValue<-1, seq_t>::value == 6, "");
    //static_assert(IntegerSequenceValue<6, seq_t>::value == 6, "");

    // NOTE: following is an expected assertion failure.
    //using empty_seq_t = integer_sequence<int>;
    //static_assert(IntegerSequenceValue<0, empty_seq_t>::value == 0, "");
}

TEST_CASE("bool value sequence inversion", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using bool_t = integer_sequence<int, 1, 1, 0, 1, 0>;
    using inverted_bool_t = integer_sequence<int, 0, 0, 1, 0, 1>;
    static_assert(
            is_same<inverted_bool_t, typename InvertBoolSequence<bool_t>::type>(),
            "inverted bool_t should be same as inverted_bool_t."
    );
}

