#include "../catch.hpp"

#include "rocky/base/TypeListWrap.h"


TEST_CASE("WarpAsTypeList", "[WrapAsTypeList]")
{
    using std::is_same;
    using std::tuple;

    static_assert(is_same<TL<TL<>, TL<>>, WrapAsTypeListT<TL<>, TL<>>>(), "");
    static_assert(is_same<TL<TL<char>, TL<>>, WrapAsTypeListT<TL<char>, TL<>>>(), "");
    static_assert(is_same<TL<TL<>, TL<char>>, WrapAsTypeListT<TL<>, TL<char>>>(), "");
    static_assert(
            is_same<TL<TL<char>, TL<char>>, WrapAsTypeListT<TL<char>, TL<char>>>(),
            ""
    );

    static_assert(
            is_same<TL<TL<char>, char, int>, WrapAsTypeListT<TL<char>, char, int>>(),
            ""
    );
    static_assert(
            is_same<TL<char, TL<char, int>>, WrapAsTypeListT<char, TL<char, int>>>(),
            ""
    );
}

TEST_CASE("TypeList operator +", "[TypeListJoin]")
{
    using std::is_same;
    using std::decay_t;

    constexpr auto crt = TL<char, int>{} + TL<float, double>{};
    static_assert(is_same<decay_t<decltype(crt)>, TL<TL<char, int>, TL<float, double>>>(), "");

    auto rt = TL<char, int>{} + TL<float, double>{};
    static_assert(is_same<decltype(rt), TL<TL<char, int>, TL<float, double>>>(), "");
}

