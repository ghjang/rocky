#include "../catch.hpp"

#include <type_traits>

#include "rocky/et/ReplaceOpTag.h"
#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"


TEST_CASE("replace OpTag", "[et]")
{
    {
        auto expr = _1 + 1;
        auto expr1 = _1 - 1;
        static_assert(
            std::is_same<
                ReplaceOpTagT<decltype(expr), addition_t, subtraction_t>,
                decltype(expr1)
            >()
        );
    }

    {
        auto expr = _1 * (1 + _2);
        auto expr1 = _1 * (1 - _2);
        static_assert(
            std::is_same<
                ReplaceOpTagT<decltype(expr), addition_t, subtraction_t>,
                decltype(expr1)
            >()
        );
    }

    {
        auto expr = -_1 + 1;
        auto expr1 = -_1 - 1;
        static_assert(
            std::is_same<
                ReplaceOpTagT<decltype(expr), addition_t, subtraction_t>,
                decltype(expr1)
            >()
        );
    }

    {
        auto expr = _1 ^ 1;
        static_assert(
            std::is_same<
                ReplaceOpTagT<decltype(expr), bitwise_xor_t, pow_t>,
                expression<place_holder<1>, pow_t, value_holder<true, int>, false, true, functor, default_storage>
            >()
        );
    }
}
