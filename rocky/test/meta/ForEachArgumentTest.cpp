#include "../catch.hpp"

#include "rocky/meta/ForEachArgument.h"

#include <type_traits>


namespace
{
    int g_intSum = 0;
    void SumFunc(int i)
    {
        g_intSum += i;
    }
}

TEST_CASE("for each argument", "[ForEachArgument]")
{
    using std::is_same;

    struct Sum
    {
        Sum() : s_{} { }
        int operator () (int i)
        {
            s_ += i;
            return s_;
        }
        int s_;
    };

    struct Sum1
    {
        Sum1() : s_{} { }
        void operator () (int i) // void return type
        {
            s_ += i;
        }
        int s_;
    };

    // by using traditional functors

    decltype(auto) sum = ForEachArgument(Sum(), 1, 2, 3, 4, 5);
    static_assert(is_same<Sum &&, decltype(sum)>(), "sum's type is Sum &&.");
    REQUIRE(sum.s_ == 15);

    decltype(auto) sum1 = ForEachArgument(Sum1(), 1, 2, 3, 4, 5);
    static_assert(is_same<Sum1 &&, decltype(sum1)>(), "sum1's type is Sum1 &&.");
    REQUIRE(sum1.s_ == 15);

    auto sum2 = ForEachArgument(Sum(), 1, 2, 3, 4, 5);
    static_assert(is_same<Sum, decltype(sum2)>(), "sum2's type is Sum.");
    REQUIRE(sum2.s_ == 15);

    auto const & sum3 = ForEachArgument(Sum(), 1, 2, 3, 4, 5);
    static_assert(is_same<Sum const &, decltype(sum3)>(), "sum3's type is Sum const &.");
    REQUIRE(sum3.s_ == 15);

    auto && sum4 = ForEachArgument(Sum(), 1, 2, 3, 4, 5);
    static_assert(is_same<Sum &&, decltype(sum4)>(), "sum4's type is Sum &&.");
    REQUIRE(sum4.s_ == 15);

    // by using lambda function
    int intSum = 0;
    ForEachArgument([&intSum](int i) { intSum += i; }, 1, 2, 3, 4, 5);
    REQUIRE(intSum == 15);

    // by using c-style function
    ForEachArgument(&SumFunc, 1, 2, 3, 4, 5);
    REQUIRE(g_intSum == 15);
}

