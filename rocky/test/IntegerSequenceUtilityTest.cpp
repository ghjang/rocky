#include "catch.hpp"

#include "rocky/meta/IntegerSequenceUtility.h"

#include <type_traits>


namespace
{
    constexpr int SquareInt(int i) { return i * i; }

    template <std::size_t i>
    struct SquareIntGenerator
    {
        constexpr static std::size_t value = SquareInt(i);
    };

    constexpr int Factorial(int i)
    {
        if (i == 0) {
            return 1;
        }
        return i * Factorial(i - 1);
    }

    template <std::size_t i>
    struct FactorialGenerator
    {
        constexpr static std::size_t value = Factorial(i);
    };
}


TEST_CASE("squared integer sequence", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using square_int_seq = typename CustomIntegerSequence<4, SquareIntGenerator>::type;
    static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq>(), "");

    using square_int_seq_1 = MakeCustomIntegerSequence<4, SquareIntGenerator>;
    static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq_1>(), "");
    static_assert(is_same<square_int_seq, square_int_seq_1>(), "");
}

TEST_CASE("factorial integer sequence", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using factorial_int_seq = MakeCustomIntegerSequence<5, FactorialGenerator>;
    static_assert(is_same<integer_sequence<std::size_t, 1, 1, 2, 6, 24>, factorial_int_seq>(), "");
}

TEST_CASE("join integer sequence", "[IntegerSequenceUtility]")
{
    using std::is_same;
    using std::integer_sequence;

    using seq1_t = integer_sequence<int, 1, 2, 3>;
    using seq2_t = integer_sequence<int, 4, 5, 6>;
    using joined_t = integer_sequence<int, 1, 2, 3, 4, 5, 6>;
    using reverse_joined_t = integer_sequence<int, 4, 5, 6, 1, 2, 3>;
    static_assert(is_same<joined_t, typename JoinIntegerSequence<seq1_t, seq2_t>::type>(), "");
    static_assert(is_same<reverse_joined_t, typename JoinIntegerSequence<seq2_t, seq1_t>::type>(), "");

    // NOTE: following is an expected static assertion failure.
    /*
    using seq3_t = integer_sequence<uint, 1, 2, 3>;
    typename JoinIntegerSequence<seq1_t, seq3_t>::type seq;
     */
}

TEST_CASE("integer sequence length", "[IntegerSequenceUtility]")
{
    using std::integer_sequence;

    using empty_seq_t = integer_sequence<int>;
    static_assert(0 == IntegerSequenceLength<empty_seq_t>(), "");

    using seq1_t = integer_sequence<int, 1, 2, 3>;
    static_assert(3 == IntegerSequenceLength<seq1_t>(), "");
}

