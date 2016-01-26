#include "../catch.hpp"

#include "rocky/skull/TakeWhile.h"

#include "rocky/base/TypeUtility.h"


TEST_CASE("TakeWhile", "[skull]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;

    static_assert(
            is_same<
                    TypeList<>,
                    TakeWhileT<is_integral>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int>,
                    TakeWhileT<is_integral, char, int, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int, long, long long>,
                    TakeWhileT<is_integral, char, int, long, long long>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<>,
                    TakeWhileT<NegatePredicate<is_integral>::template Convert, char, int, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<char, int>,
                    TakeWhileT<is_integral, TypeList<char, int, float, double>>
            >(),
            ""
    );

    static_assert(
            is_same<
                    tuple<char, int>,
                    TakeWhileT<is_integral, tuple<char, int, float, double>>
            >(),
            ""
    );
}

