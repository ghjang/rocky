#include "../catch.hpp"

#include "rocky/skull/Take.h"

#include <type_traits>


TEST_CASE("Take", "[skull]")
{
    using std::is_same;

    static_assert(
            is_same<TypeList<>, typename Take<0, TypeList<char, int, float, double>>::type>(), ""
    );
    /*
    static_assert(
            is_same<TypeList<char>, typename Take<1, TypeList<char, int, float, double>>::type>(), ""
    );
    static_assert(
            is_same<TypeList<char, int>, typename Take<2, TypeList<char, int, float, double>>::type>(), ""
    );
    static_assert(
            is_same<
                TypeList<char, int, float, double>,
                typename Take<5, TypeList<char, int, float, double>>::type
            >(),
            ""
    );
     */
}

