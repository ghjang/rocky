#include "catch.hpp"

#include "rocky/meta/CharSequenceUtility.h"


TEST_CASE("char sequence", "[CharSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using charseq_t = integer_sequence<char, 'a', 'b', 'c'>;
    static_assert(is_same<charseq_t, CharSequence<'a', 'b', 'c'>>(), "");
}

TEST_CASE("join char sequence", "[CharSequenceUtility]")
{
    using std::is_same;

    using charseq1_t = CharSequence<'a', 'b', 'c'>;
    using charseq2_t = CharSequence<'d', 'e', 'f'>;
    using joined_charseq_t = CharSequence<'a', 'b', 'c', 'd','e','f'>;
    static_assert(is_same<joined_charseq_t, typename JoinCharSequence<charseq1_t, charseq2_t>::type>(), "");
}

TEST_CASE("making char sequence from integer", "[CharSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using charseq_t = integer_sequence<char, '1', '2', '3'>;
    static_assert(is_same<charseq_t, typename MakeCharSequenceFromInteger<123>::type>(), "");

    using negative_charseq_t = integer_sequence<char, '-', '1', '2', '3'>;
    static_assert(is_same<negative_charseq_t, typename MakeCharSequenceFromInteger<-123>::type>(), "");
}

TEST_CASE("char sequence length", "[CharSequenceUtility]")
{
    using empty_seq_t = CharSequence<>;
    static_assert(0 == CharSequenceLength<empty_seq_t>(), "");

    using seq1_t = CharSequence<'1', '2', '3'>;
    static_assert(3 == CharSequenceLength<seq1_t>(), "");
}
