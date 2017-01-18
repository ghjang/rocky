#include "../catch.hpp"

#include <iostream>

#include <range/v3/all.hpp>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/MathFunction.h"
#include "rocky/et/PlaceHolderDef.h"

#include "rocky/math/NumberSequence.h"
#include "rocky/math/NumberSequence2.h"
#include "rocky/math/NumberCompare.h"


TEST_CASE("number sequence with range and et", "[et]")
{
    using namespace ranges;

    auto generator = number_seq(2 * _1 + 1);
    std::vector<int> seq = view::generate(generator) | view::take(3);
    REQUIRE(ranges::equal(seq, { 1, 3, 5 }));

    auto generator1 = number_seq(2 * _1 + 1, 10);
    std::vector<int> seq1 = view::generate(generator1) | view::take(3);
    REQUIRE(ranges::equal(seq1, { 21, 23, 25 }));

    auto generator2 = number_seq(2 * _1 + 1, 10, 10);
    std::vector<int> seq2 = view::generate(generator2) | view::take(3);
    REQUIRE(ranges::equal(seq2, { 21, 41, 61 }));
}

TEST_CASE("number sequence with range and et - 1", "[et]")
{
    using namespace ranges;

    auto sin = number_seq(sin_[_1], 0, M_PI_2);
    std::vector<double> seq = view::generate(sin) | view::take(4);

    // NOTE: If a generic lambda is used, then it results in a compiler error:
    //
    //          ranges::for_each(seq, [](auto a){ std::cout << a << '\n'; });
    //
    //       The current implementation seems not to handle this case correctly.

    //ranges::for_each(seq, [](double a){ std::cout << a << '\n'; });

    REQUIRE(ranges::equal(
                seq,
                { 0, 1, 0, -1 },
                [](double a, double b){
                    //std::cout << "a: " << a << ", b: " << b << '\n';
                    return is_almost_equal(a, b);
                }
            ));
}

TEST_CASE("number sequence with range and et - 2", "[et]")
{
    using namespace ranges;

    auto sin = number_seq(sin_[_1] + 1, 0, M_PI_2);
    std::vector<double> seq = view::generate(sin) | view::take(4);
    
    //ranges::for_each(seq, [](double a){ std::cout << a << '\n'; });

    REQUIRE(ranges::equal(
                seq,
                { 1, 2, 1, 0 },
                [](double a, double b) {
                    //std::cout << "a: " << a << ", b: " << b << '\n';
                    return is_almost_equal(a, b, 2);
                }
            ));
}

TEST_CASE("number sequence with range and et - 3", "[et]")
{
    using namespace ranges;

    auto sin = number_seq(10 * sin_[2 * _1] + 5, 0, M_PI_2);
    std::vector<double> seq = view::generate(sin) | view::take(4);
    REQUIRE(ranges::equal(
                seq,
                { 5, 5, 5, 5 },
                [](double a, double b) {
                    //std::cout << "a: " << a << ", b: " << b << '\n';
                    return is_almost_equal(a, b, 20); // TODO, FIXME: how do we decide a correct ulp argument value?
                }
            ));

    auto sin1 = number_seq(10 * sin_[3 * _1] + 5, 0, M_PI_2);
    std::vector<double> seq1 = view::generate(sin1) | view::take(4);
    REQUIRE(ranges::equal(
                seq1,
                { 5, -5, 5, 15 },
                [](double a, double b) {
                    //std::cout << "a: " << a << ", b: " << b << '\n';
                    return is_almost_equal(a, b, 20); // TODO, FIXME: how do we decide a correct ulp argument value?
                }
            ));
}

TEST_CASE("number sequence with range and et - 4", "[et]")
{
    using namespace ranges;

    // NOTE: '^' is a normal bitwise operator here.
    auto gen = number_seq(0xFF ^ _1);
    std::vector<int> seq = view::generate(gen) | view::take(3);
    REQUIRE(ranges::equal(seq, { 0xFF, 0xFE, 0xFD }));

    // NOTE: number_seq2 will replace bitwise_xor_t type
    //          in the expression template type tree with pow_t type.
    //          This means that '^' will be used as a power operator
    //          rather than bitwise xor one.
    auto gen1 = number_seq2(2 ^ _1);
    std::vector<int> seq1 = view::generate(gen1) | view::take(5);
    REQUIRE(ranges::equal(seq1, { 1, 2, 4, 8, 16 }));

    // NOTE: This doesn't compile... FIXME if it is possible...
    /*
    auto gen2 = number_seq2((2 ^ _1) + 10);
    std::vector<int> seq2 = view::generate(gen2) | view::take(5);
    REQUIRE(ranges::equal(seq2, { 10, 12, 14, 18, 26 }));
    */
}
