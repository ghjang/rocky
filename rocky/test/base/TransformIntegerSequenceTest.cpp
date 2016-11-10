#include "../catch.hpp"

#include "rocky/base/TransformIntegerSequence.h"


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


TEST_CASE("TransformIntegerSequence", "[TransformIntegerSequence]")
{
    // NOTE: this is an expected static assertion failure.
    //typename TransformIntegerSequence<SquareIntGenerator, std::integer_sequence<std::size_t>>::type();
}

TEST_CASE("squared integer sequence", "[TransformIntegerSequence]")
{
    using std::is_same;
    using std::integer_sequence;

    using square_int_seq = typename TransformIntegerSequence<
                                            SquareIntGenerator,
                                            std::make_integer_sequence<std::size_t, 4>
                                        >::type;
    static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq>());

    using square_int_seq_1 = MakeCustomIntegerSequence<SquareIntGenerator, 4>;
    static_assert(is_same<integer_sequence<std::size_t, 0, 1, 4, 9>, square_int_seq_1>());
    static_assert(is_same<square_int_seq, square_int_seq_1>());
}

TEST_CASE("factorial integer sequence", "[TransformIntegerSequence]")
{
    using std::is_same;
    using std::integer_sequence;

    using factorial_int_seq = MakeCustomIntegerSequence<FactorialGenerator, 5>;
    static_assert(is_same<integer_sequence<std::size_t, 1, 1, 2, 6, 24>, factorial_int_seq>());
}

