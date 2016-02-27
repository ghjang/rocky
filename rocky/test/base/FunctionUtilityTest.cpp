#include "../catch.hpp"

#include "rocky/base/FunctionUtility.h"


TEST_CASE("FunctionParameterListSize", "[FunctionUtility]")
{
    static_assert(1 == FunctionParameterListSize<decltype(fclose)>(), "");
    static_assert(1 == FunctionParameterListSize<decltype((fclose))>(), "");
    static_assert(1 == FunctionParameterListSize<decltype(&fclose)>(), "");

    static_assert(2 == FunctionParameterListSize<decltype(fopen)>(), "");

    static_assert(0 == FunctionParameterListSize<decltype(getchar)>(), "");
}

