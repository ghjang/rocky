#include "../catch.hpp"

#include "rocky/meta/TypeList.h"

#include <type_traits>


TEST_CASE("TypeList join", "[TypeList]")
{
    using std::is_same;

    static_assert(
            is_same<
                TypeList<char, int, float, double>,
                typename JoinTypeList<TypeList<char, int>, TypeList<float, double>>::type
            >(),
            ""
    );

    static_assert(
            is_same<
                TypeList<char, int, float, double>,
                typename JoinTypeList<TypeList<char, int>, float, double>::type
            >(),
            ""
    );

    /**
     * following is not a valid pattern matching.
     */
    /*
    static_assert(
            is_same<
                    TypeList<char, int, float, double>,
                    typename JoinTypeList<char, int, TypeList<float, double>>::type
            >(),
            ""
    );
     */
}

TEST_CASE("TypeList operator +", "[TypeList]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TypeList<char, int, float, double>>(), "");

    auto rt = TypeList<char, int>{} + TypeList<float, double>{};
    static_assert(is_same<decltype(rt), TypeList<char, int, float, double>>(), "");
}

