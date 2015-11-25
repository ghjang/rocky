#include "catch.hpp"


#include "rocky/meta/ForEachTupleElement.h"

#include <type_traits>


TEST_CASE("for each tuple element", "[ForEachTupleElement]")
{
    using std::tuple;
    using std::make_tuple;

    {
        struct Sum
        {
            int sum_;
            Sum() : sum_(0) { }
            void operator()(int i) { sum_ += i; }
        };

        auto sumObj = ForEachTupleElement(Sum(), make_tuple(1, 2, 3, 4, 5));
        REQUIRE(15 == sumObj.sum_);
    }

    {
        int sum = 0;
        ForEachTupleElement([&sum](int i) { sum += i; }, make_tuple(1, 2, 3, 4, 5));
        REQUIRE(15 == sum);
    }
}

