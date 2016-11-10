#include "../catch.hpp"

#include "rocky/skull/Replicate.h"

#include "rocky/base/IntegerSequenceUtility.h"


TEST_CASE("Replicate", "[skull]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TypeList<>, ReplicateT<0, char>>());

    static_assert(
            is_same<
                    TypeList<int_c_t<0>, int_c_t<0>, int_c_t<0>>,
                    ReplicateT<3, int_c_t<0>>
            >()
    );

    static_assert(is_same<TypeList<char, char, char>, ReplicateT<3, char>>());
    static_assert(
            is_same<
                    TypeList<TypeList<char>, TypeList<char>, TypeList<char>>,
                    ReplicateT<3, TypeList<char>>
            >()
    );
}

TEST_CASE("Replicating std::integral_constant", "[skull]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    integer_sequence<int, 5, 5, 5>,
                    IntConstListToIntSeqT<ReplicateT<3, int_c_t<5>>>
            >()
    );
}

