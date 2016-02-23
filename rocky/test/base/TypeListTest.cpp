#include "../catch.hpp"

#include "rocky/base/TypeList.h"

#include "rocky/base/TypeComposition.h"
#include "rocky/skull/Map.h"


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

TEST_CASE("ReplaceTypeListContainer", "[TypeList]")
{
    using std::is_same;
    using std::tuple;

    static_assert(
            is_same<
                    tuple<char, int, float, double>,
                    ReplaceTypeListContainerT<TypeList<char, int, float, double>, tuple>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TL<tuple<char, int>, tuple<float, double>>,
                    MapT<
                            QuoteReplaceTypeListContainer<tuple>,
                            TL<TL<char, int>, TL<float, double>>
                    >
            >(),
            ""
    );
}

