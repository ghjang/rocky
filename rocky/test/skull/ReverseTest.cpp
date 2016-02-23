#include "../catch.hpp"

#include "rocky/skull/Reverse.h"


TEST_CASE("Reversing tuple's template parameters", "[Reverse]")
{
    using std::is_same;
    using std::tuple;

    static_assert(
            is_same<
                    TypeList<double, float, int, short, char>,
                    ReverseT<char, short, int, float, double>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<double, float, int, short, char>,
                    ReverseT<TypeList<char, short, int, float, double>>
            >(),
            ""
    );

    using T = tuple<char, short, int, float, double>;
    using ReversedT = tuple<double, float, int, short, char>;
    static_assert(is_same<ReverseT<T>, ReversedT>(), "ReverseT<T>::type should be ReversedT.");
}

