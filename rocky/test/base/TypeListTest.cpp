#include "../catch.hpp"

#include "rocky/base/TypeList.h"


TEST_CASE("TypeListSize", "[TypeList]")
{
    static_assert(0 == TypeListSize<>(), "");
    static_assert(1 == TypeListSize<int>(), "");
    static_assert(3 == TypeListSize<char, int, float>(), "");

    static_assert(0 == TypeListSize<TypeList<>>(), "");
    static_assert(1 == TypeListSize<TypeList<int>>(), "");
    static_assert(3 == TypeListSize<TypeList<char, int, float>>(), "");
}

TEST_CASE("FunctionParameterListSize", "[TypeList]")
{
    static_assert(1 == FunctionParameterListSize<decltype(fclose)>(), "");
    static_assert(1 == FunctionParameterListSize<decltype((fclose))>(), "");
    static_assert(1 == FunctionParameterListSize<decltype(&fclose)>(), "");

    static_assert(2 == FunctionParameterListSize<decltype(fopen)>(), "");

    static_assert(0 == FunctionParameterListSize<decltype(getchar)>(), "");
}

