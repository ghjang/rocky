#include "../catch.hpp"

#include "rocky/wolca/Flatten.h"


TEST_CASE("Flatten", "[wolca]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TL<>, FlattenT<>>());
    static_assert(is_same<TL<>, FlattenT<TL<>>>());
    static_assert(is_same<TL<>, FlattenT<TL<TL<>>>>());
    static_assert(is_same<TL<>, FlattenT<TL<>, TL<TL<>>>>());

    static_assert(is_same<TL<char>, FlattenT<char>>());
    static_assert(is_same<TL<char>, FlattenT<TL<char>>>());

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenT<char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenT<TL<char, int>, float, TL<double>>
            >()
    );

    static_assert(
            is_same<
                    TL<char, int, float, double>,
                    FlattenT<TL<TL<char, int>, float, TL<double>>>
            >()
    );

    static_assert(
            is_same<
                    TL<char, int, long, long, float, double>,
                    FlattenT<TL<TL<char, int, TL<long, long>>, float, TL<double>>>
            >()
    );

    static_assert(
            is_same<
                    tuple<char, int, long, long, float, double>,
                    FlattenT<tuple<TL<char, int, TL<long, long>>, float, TL<double>>>
            >()
    );

    static_assert(
            is_same<
                    tuple<char, int, long, long, float, long double, double>,
                    FlattenT<tuple<TL<char, int, tuple<long, long>>, float, tuple<long double>, TL<double>>>
            >()
    );

    static_assert(
            is_same<
                    TL<char, int, long, long, float, long double, double>,
                    FlattenT<TL<TL<char, int, tuple<long, long>>, float, tuple<long double>, TL<double>>>
            >()
    );
}

