#include "../catch.hpp"

#include "rocky/base/TypeComposition.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Filter.h"
#include "rocky/skull/Replicate.h"


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
                    >
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
                    >
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
                    >
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
                    >
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
                    >
            >(),
            ""
    );

    static_assert(HasApplyMember<Compose<ReplicateT<3, Quote<add_pointer>>>>(), "");
    static_assert(is_same<int ***, ApplyT<Compose<ReplicateT<3, Quote<add_pointer>>>, int>>(), "");
    static_assert(
            is_same<
                    int ***,
                    ApplyT<
                            Compose<
                                    FlattenAsTypeListT<
                                            ReplicateT<3, Quote<add_pointer>>,
                                            Quote<Head>, Quote<Filter>
                                    >
                            >,
                            Quote<is_integral>, float, double, int, char, long
                    >
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

TEST_CASE("BindFirst", "[TypeComposition]")
{
    using std::is_same;

    static_assert(ApplyT<BindFirst<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<BindFirst<Quote<is_same>, char>, int>(), "");

    // NOTE: it's possible to bind n-type.
    static_assert(ApplyT<BindFirst<Quote<is_same>, char, char>>(), "");
    static_assert(!ApplyT<BindFirst<Quote<is_same>, char, int>>(), "");
}

TEST_CASE("BindLast", "[TypeComposition]")
{
    using std::is_same;

    static_assert(ApplyT<BindLast<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<BindLast<Quote<is_same>, char>, int>(), "");

    // NOTE: it's possible to bind n-type.
    static_assert(ApplyT<BindLast<Quote<is_same>, char, char>>(), "");
    static_assert(!ApplyT<BindLast<Quote<is_same>, char, int>>(), "");
}

