#include "../catch.hpp"

#include "rocky/skull/TakeWhile.h"

#include "rocky/base/TypeUtility.h"


TEST_CASE("TakeWhile", "[skull]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;

    static_assert(is_same<TypeList<>, TakeWhileT<Quote<is_integral>>>(), "");

    static_assert(
            is_same<
                    TypeList<char, int>,
                    TakeWhileT<Quote<is_integral>, char, int, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, long, long long>,
                    TakeWhileT<Quote<is_integral>, char, int, long, long long>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<>,
                    TakeWhileT<NegatePredicate<Quote<is_integral>>, char, int, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int>,
                    TakeWhileT<Quote<is_integral>, TypeList<char, int, float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<char, int>,
                    TakeWhileT<Quote<is_integral>, tuple<char, int, float, double>>
            >(),
            ""
    );
}

