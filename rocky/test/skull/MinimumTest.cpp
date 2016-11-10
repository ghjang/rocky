#include "../catch.hpp"

#include "rocky/skull/Minimum.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Minimum for std::integral_constant", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // NOTE: following are expected compile-time errors.
    //static_assert(0 == MinimumT<>());
    //static_assert(0 == MinimumT<TypeList<>>());
    //static_assert(0 == MinimumT<tuple<>>());

    static_assert(0 == MinimumT<int_c_t<1>, int_c_t<0>, int_c_t<2>>());
    static_assert(is_same<int_c_t<0>, MinimumT<int_c_t<1>, int_c_t<0>, int_c_t<2>>>());

    static_assert(0 == MinimumT<TypeList<int_c_t<0>, int_c_t<2>, int_c_t<1>>>());
    static_assert(is_same<int_c_t<0>, MinimumT<TypeList<int_c_t<0>, int_c_t<2>, int_c_t<1>>>>());

    static_assert(0 == MinimumT<tuple<int_c_t<0>, int_c_t<2>, int_c_t<1>>>());
    static_assert(is_same<int_c_t<0>, MinimumT<tuple<int_c_t<0>, int_c_t<2>, int_c_t<1>>>>());
}

