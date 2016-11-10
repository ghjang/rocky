#include "../catch.hpp"

#include "rocky/wolca/Riffle.h"

#include "rocky/base/IntegralConstantUtility.h"


TEST_CASE("Riffle", "[wolca]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TL<>, RiffleT<char_c_t<'b'>>>());
    static_assert(is_same<TL<char>, RiffleT<char_c_t<'b'>, char>>());
    static_assert(is_same<TL<char, char_c_t<'b'>, int>, RiffleT<char_c_t<'b'>, char, int>>());

    static_assert(
            is_same<
                    TL<char, char_c_t<'b'>, int, char_c_t<'b'>, float, char_c_t<'b'>, double>,
                    RiffleT<char_c_t<'b'>, char, int, float, double>
            >()
    );

    static_assert(
            is_same<
                    TL<char, char_c_t<'b'>, int, char_c_t<'b'>, float, char_c_t<'b'>, double>,
                    RiffleT<char_c_t<'b'>, TypeList<char, int, float, double>>
            >()
    );

    static_assert(
            is_same<
                    tuple<char, char_c_t<'b'>, int, char_c_t<'b'>, float, char_c_t<'b'>, double>,
                    RiffleT<char_c_t<'b'>, tuple<char, int, float, double>>
            >()
    );
}

