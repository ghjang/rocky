#include "catch.hpp"

#include "rocky/meta/CharSequenceUtility.h"


TEST_CASE("char sequence", "[CharSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using charseq_t = integer_sequence<char, 'a', 'b', 'c'>;
    static_assert(is_same<charseq_t, CharSequence<'a', 'b', 'c'>>(), "");
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

