#include "../catch.hpp"

#include "rocky/wolca/Partition.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Partition", "[wolca]")
{
    using std::is_same;

    // NOTE: exptected compile-time errors.
    /*
    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    PartitionT<int_c_t<-1>, char, int, float, double>
            >()
    );
    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    PartitionT<int_c_t<0>, char, int, float, double>
            >()
    );
     */

    static_assert(
            is_same<
                    TL<>,
                    PartitionT<int_c_t<1>>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char>, TL<int>, TL<float>, TL<double>>,
                    PartitionT<int_c_t<1>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    PartitionT<int_c_t<2>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int, float>>,
                    PartitionT<int_c_t<3>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int, float, double>>,
                    PartitionT<int_c_t<4>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<>,
                    PartitionT<int_c_t<5>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char>, TL<int>, TL<float>, TL<double>>,
                    PartitionT<int_c_t<1>, TypeList<char, int, float, double>>
            >()
    );
}

TEST_CASE("ListToPair type alias", "[wolca]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TL<>,
                    ListToPairT<>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    ListToPairT<char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    ListToPairT<char, int, float, double, int>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int>, TL<float, double>>,
                    ListToPairT<TypeList<char, int, float, double, int>>
            >()
    );
 }

