#include "../catch.hpp"

#include "rocky/skull/Map.h"


TEST_CASE("Map", "[skull]")
{
    using std::is_same;
    using std::tuple;
    using std::add_pointer;

    static_assert(is_same<TypeList<>, MapT<Quote<add_pointer>>>(), "");
    static_assert(is_same<TypeList<>, MapT<Quote<add_pointer>, TypeList<>>>(), "");
    static_assert(is_same<tuple<>, MapT<Quote<add_pointer>, tuple<>>>(), "");

    static_assert(
            is_same<TypeList<char *, int *, float *, double *>, MapT<Quote<add_pointer>, char, int, float, double>>(),
            ""
    );
    static_assert(
            is_same<
                    TypeList<char *, int *, float *, double *>,
                    MapT<Quote<add_pointer>, TypeList<char, int, float, double>>
            >(),
            ""
    );
    static_assert(
            is_same<
                    tuple<char *, int *, float *, double *>,
                    MapT<Quote<add_pointer>, tuple<char, int, float, double>>
            >(),
            ""
    );
}

