#include "catch.hpp"


#include "rocky/meta/ForEachTuple.h"

#include <type_traits>


namespace
{
    struct Sum
    {
        std::size_t sum_;

        Sum() : sum_(0) { }

        template <typename T>
        void operator () (T && t)
        {
            sum_ += TypeSizeOf(t);
        }
    };
}


TEST_CASE("for each tuple element", "[ForEachTuple]")
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

        auto sumObj = ForEachElement(Sum(), make_tuple(1, 2, 3, 4, 5));
        REQUIRE(15 == sumObj.sum_);
    }

    {
        int sum = 0;
        ForEachElement([&sum](int i) { sum += i; }, make_tuple(1, 2, 3, 4, 5));
        REQUIRE(15 == sum);
    }
}

TEST_CASE("tuple element type size sum", "[ForEachTuple]")
{
    using std::make_tuple;

    {
        auto sumObj = ForEachElementType(Sum(), make_tuple(1, 1, 1));
        REQUIRE(sizeof(int) * 3 == sumObj.sum_);
    }

    {
        int typeSizeSum = 0;
        ForEachElementType([&typeSizeSum](auto t) { typeSizeSum += TypeSizeOf(t); }, make_tuple(1, 2, 3, 4, 5));
        REQUIRE(sizeof(int) * 5 == typeSizeSum);
    }

    {
        struct LocalObj
        {
            int i_;
            char c_;
        };
        int typeSizeSum = 0;
        ForEachElementType(
                [&typeSizeSum](auto t) { typeSizeSum += TypeSizeOf(t); },
                make_tuple(1, 2, LocalObj(), 3, LocalObj())
        );
        REQUIRE(sizeof(int) * 3 + sizeof(LocalObj) * 2 == typeSizeSum);
    }
}

