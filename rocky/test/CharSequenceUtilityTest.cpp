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
    using joined_charseq1_t = CharSequence<'a', 'b', 'c', 'd', 'e', 'f'>;
    static_assert(is_same<joined_charseq1_t, typename JoinCharSequence<charseq1_t, charseq2_t>::type>(), "");

    using charseq3_t = CharSequence<'g', 'h', 'i'>;
    using joined_charseq2_t = CharSequence<'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'>;
    static_assert(
            is_same<joined_charseq2_t, typename JoinCharSequence<charseq1_t, charseq2_t, charseq3_t>::type>(), ""
    );
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

TEST_CASE("char_array_c", "[CharSequenceUtility]")
{
    using empty_seq_t = CharSequence<>;
    REQUIRE(std::string("") == char_array_c<empty_seq_t>);

    using seq1_t = CharSequence<'1', '2', '3'>;
    REQUIRE(std::string("123") == char_array_c<seq1_t>);

    using seq2_t = CharSequence<'-', '1', '2', '3'>;
    REQUIRE(std::string("-123") == char_array_c<seq2_t>);

    using seq3_t = CharSequence<'-', '-', '-', '-'>;
    REQUIRE(std::string("----") == char_array_c<seq3_t>);
}

TEST_CASE("MakeStringFromInteger", "[CharSequenceUtility]")
{
    constexpr auto s1 = ToConstExprString<123>();
    REQUIRE(strcmp(s1, "123") == 0);

    constexpr auto s2 = ToConstExprString<-123>();
    REQUIRE(strcmp(s2, "-123") == 0);
}

