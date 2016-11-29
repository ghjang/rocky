#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"


TEST_CASE("is_expression meta-function", "[et]")
{
    static_assert(!is_expression<std::decay_t<decltype(_1)>>::value);
    static_assert(is_expression<std::decay_t<decltype(_1 + 1)>>::value);
}

TEST_CASE("is_terminal meta-function", "[et]")
{
    static_assert(is_terminal<std::decay_t<decltype(_1)>>::value);
    static_assert(!is_terminal<std::decay_t<decltype(_1 + 1)>>::value);

    value_holder<true, int> vh{ 1 };
    static_assert(is_terminal<std::decay_t<decltype(vh)>>::value);
}
