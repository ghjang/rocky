#include "../catch.hpp"

#include "rocky/skull/ZipWith.h"

#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/base/TypeListUtility.h"
#include "rocky/skull/Replicate.h"
#include "rocky/skull/Range.h"
#include "rocky/skull/Max.h"
#include "rocky/skull/Map.h"


TEST_CASE("ZipWith", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(
            is_same<
                    TypeList<>,
                    MapT<
                            Quote<ToTuple>,
                            ZipWithT<Quote<AsPairTuple>, TypeList<>, TypeList<>>
                    >
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<tuple<char, int>, tuple<char, int>>,
                    MapT<
                            Quote<ToTuple>,
                            ZipWithT<Quote<AsPairTuple>, TypeList<char, char>, TypeList<int, int>>
                    >
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<tuple<char, int>, tuple<char, int>>,
                    ToTupleT<TypeList<tuple<char, int>, tuple<char, int>>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<tuple<char, int>, tuple<char, int>>,
                    ToTupleT<ZipWithT<Quote<AsPairTuple>, TypeList<char, char>, TypeList<int, int>>>
            >(),
            ""
    );
}

TEST_CASE("ZipWith Plus", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<2>, int_c_t<4>, int_c_t<6>>,
                    ZipWithT<
                            Quote<Plus>,
                            TL<int_c_t<1>, int_c_t<2>, int_c_t<3>>,
                            TL<int_c_t<1>, int_c_t<2>, int_c_t<3>>
                    >
            >(),
            ""
    );
}

TEST_CASE("ZipWith Max", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<6>, int_c_t<7>, int_c_t<8>>,
                    ZipWithT<
                            Quote<Max>,
                            TL<int_c_t<4>, int_c_t<7>, int_c_t<8>>,
                            TL<int_c_t<6>, int_c_t<1>, int_c_t<7>>
                    >
            >(),
            ""
    );
}

TEST_CASE("ZipWith Multiply", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<int_c_t<2>, int_c_t<4>, int_c_t<6>, int_c_t<8>, int_c_t<10>>,
                    ZipWithT<
                            Quote<Multiply>,
                            ReplicateT<5, int_c_t<2>>,
                            RangeT<int_c_t<1>, int_c_t<5>>
                    >
            >(),
            ""
    );
}

