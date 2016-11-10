#include "../catch.hpp"

#include "rocky/skull/Maximum.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Maximum for std::integral_constant", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // NOTE: following are expected compile-time errors.
    //static_assert(0 == MaximumT<>());
    //static_assert(0 == MaximumT<TypeList<>>());
    //static_assert(0 == MaximumT<tuple<>>());

    static_assert(2 == MaximumT<int_c_t<0>, int_c_t<2>, int_c_t<1>>());
    static_assert(is_same<int_c_t<2>, MaximumT<int_c_t<0>, int_c_t<2>, int_c_t<1>>>());

    static_assert(2 == MaximumT<TypeList<int_c_t<0>, int_c_t<2>, int_c_t<1>>>());
    static_assert(is_same<int_c_t<2>, MaximumT<TypeList<int_c_t<0>, int_c_t<2>, int_c_t<1>>>>());

    static_assert(2 == MaximumT<tuple<int_c_t<0>, int_c_t<2>, int_c_t<1>>>());
    static_assert(is_same<int_c_t<2>, MaximumT<tuple<int_c_t<0>, int_c_t<2>, int_c_t<1>>>>());
}

