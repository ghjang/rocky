#include "../catch.hpp"

#include "rocky/base/TypeComposition.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Filter.h"


TEST_CASE("Compose", "[TypeComposition]")
{
    using std::is_same;
    using std::is_integral;
    using std::add_pointer;
    using std::add_const;

    static_assert(is_same<int, HeadT<FilterT<Quote<is_integral>, float, double, int, char, long>>>(), "");

    static_assert(HasApplyMember<Compose<Quote<Head>>>(), "");
    static_assert(
            is_same<
                    float,
                    ApplyT<
                            Compose<Quote<Head>>,
                            float, double, int, char, long
                    >::type
            >(),
            ""
    );

    static_assert(HasApplyMember<Compose<Quote<Head>, Quote<Filter>>>(), "");
    static_assert(
            is_same<
                    int,
                    ApplyT<
                            Compose<Quote<Head>, Quote<Filter>>,
                            Quote<is_integral>, float, double, int, char, long
                    >::type
            >(),
            ""
    );

    static_assert(HasApplyMember<Compose<Quote<add_pointer>, Quote<Head>, Quote<Filter>>>(), "");
    static_assert(
            is_same<
                    int *,
                    ApplyT<
                            Compose<Quote<add_pointer>, Quote<Head>, Quote<Filter>>,
                            Quote<is_integral>, float, double, int, char, long
                    >::type
            >(),
            ""
    );

    static_assert(HasApplyMember<Compose<Quote<add_pointer>, Quote<add_pointer>, Quote<Head>, Quote<Filter>>>(), "");
    static_assert(
            is_same<
                    int **,
                    ApplyT<
                            Compose<Quote<add_pointer>, Quote<add_pointer>, Quote<Head>, Quote<Filter>>,
                            Quote<is_integral>, float, double, int, char, long
                    >::type
            >(),
            ""
    );

    static_assert(HasApplyMember<Compose<Quote<add_const>, Quote<add_pointer>, Quote<Head>, Quote<Filter>>>(), "");
    static_assert(
            is_same<
                    int * const,
                    ApplyT<
                            Compose<Quote<add_const>, Quote<add_pointer>, Quote<Head>, Quote<Filter>>,
                            Quote<is_integral>, float, double, int, char, long
                    >::type
            >(),
            ""
    );
}

TEST_CASE("NegatePrdicate", "[TypeComposition]")
{
    using std::is_integral;

    static_assert(is_integral<int>(), "");
    static_assert(!ApplyT<NegatePredicate<Quote<is_integral>>, int>(), "");
}

TEST_CASE("Bind1st", "[TypeComposition]")
{
    using std::is_same;

    static_assert(ApplyT<Bind1st<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<Bind1st<Quote<is_same>, char>, int>(), "");
}

TEST_CASE("Bind2nd", "[TypeComposition]")
{
    using std::is_same;

    static_assert(ApplyT<Bind2nd<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<Bind2nd<Quote<is_same>, char>, int>(), "");
}

