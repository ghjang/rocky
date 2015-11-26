#include "catch.hpp"

#include "rocky/meta/ForEachTupleType.h"


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


TEST_CASE("tuple type size sum", "[ForEachTupleType]")
{
    using std::make_tuple;

    {
        auto sumObj = ForEachTupleType(Sum(), make_tuple(1, 1, 1));
        REQUIRE(sizeof(int) * 3 == sumObj.sum_);
    }

    {
        int typeSizeSum = 0;
        ForEachTupleType([&typeSizeSum](auto t) { typeSizeSum += TypeSizeOf(t); }, make_tuple(1, 2, 3, 4, 5));
        REQUIRE(sizeof(int) * 5 == typeSizeSum);
    }

    {
        struct LocalObj
        {
            int i_;
            char c_;
        };
        int typeSizeSum = 0;
        ForEachTupleType(
                [&typeSizeSum](auto t) { typeSizeSum += TypeSizeOf(t); },
                make_tuple(1, 2, LocalObj(), 3, LocalObj())
        );
        REQUIRE(sizeof(int) * 3 + sizeof(LocalObj) * 2 == typeSizeSum);
    }
}

