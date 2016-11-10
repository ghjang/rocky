#include "../catch.hpp"

#include "rocky/skull/Concat.h"


TEST_CASE("Concat", "[skull]")
{
    using std::is_same;
    using std::tuple;

    // NOTE: following is an expected compile-time error.
    //static_assert(is_same<TL<>, ConcatT<>>());

    static_assert(is_same<TL<>, ConcatT<TL<>>>());
    static_assert(is_same<TL<>, ConcatT<TL<>, TL<>>>());

    static_assert(is_same<TL<char, int, float, double>, ConcatT<TL<char, int>, TL<float, double>>>());
    static_assert(is_same<TL<char, int, float, double>, ConcatT<TL<char, int>, TL<>, TL<float, double>>>());

    static_assert(
            is_same<
                    tuple<char, int, float, double>,
                    ConcatT<tuple<char, int>, tuple<>, tuple<float, double>>
            >()
    );

    static_assert(
            is_same<
                    TL<TL<char, int>, TL<>, TL<float, double>>,
                    ConcatT<TL<TL<char, int>>, TL<TL<>>, TL<TL<float, double>>>
            >()
    );

    static_assert(
            is_same<
                    tuple<tuple<char, int>, tuple<>, tuple<float, double>>,
                    ConcatT<tuple<tuple<char, int>>, tuple<tuple<>>, tuple<tuple<float, double>>>
            >()
    );
}

