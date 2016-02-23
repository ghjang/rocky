#include "../catch.hpp"

#include "rocky/base/TypeComposition.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Filter.h"
#include "rocky/skull/Map.h"
#include "rocky/skull/Reverse.h"
#include "rocky/skull/Replicate.h"
#include "rocky/skull/Range.h"


TEST_CASE("Compose", "[TypeComposition]")
{
    using std::is_same;
    using std::is_integral;
    using std::is_base_of;
    using std::add_pointer;
    using std::add_const;
    using std::integer_sequence;

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

    //
    static_assert(HasApplyMember<Compose<ReplicateT<3, Quote<add_pointer>>>>(), "");
    static_assert(is_same<int ***, ApplyT<Compose<ReplicateT<3, Quote<add_pointer>>>, int>>(), "");
    static_assert(
            is_same<
                    int ***,
                    ApplyT<
                            Compose<
                                    FlattenTypeListT<
                                            ReplicateT<3, Quote<add_pointer>>,
                                            Quote<Head>, Quote<Filter>
                                    >
                            >,
                            Quote<is_integral>, float, double, int, char, long
                    >
            >(),
            ""
    );

    //
    struct B1 { };
    struct B2 { };
    struct B3 { };
    struct C1 : B1 { };
    struct C2 : B1 { };
    struct C3 : B2 { };
    struct C4 : B2 { };
    struct C5 : B3 { };

    static_assert(
            is_same<
                    TypeList<C3 *, C4 *>,
                    ApplyT<
                            Compose<
                                    BindFirst<Quote<Map>, Quote<add_pointer>>,
                                    Quote<Filter>
                            >,
                            BindFirst<Quote<is_base_of>, B2>, C1, C2, C3, C4, C5
                    >
            >(),
            ""
    );

    //
    static_assert(
            is_same<
                    integer_sequence<int, 20, 16, 12, 8, 4>,
                    ApplyT<
                            Compose<
                                    Quote<IntegralConstantListToIntegerSequence>,
                                    BindFirst<
                                            Quote<Map>,
                                            BindLast<Quote<Multiply>, int_c_t<2>>
                                    >,
                                    Quote<Reverse>
                            >,
                            MakeEvenRangeT<1, 10>
                    >
            >(),
            ""
    );

    // Ooops!
    static_assert(
            is_same<
                    TypeList<double, TypeList<>>,
                    ApplyT<
                            Compose<
                                    Quote<FlattenTypeList>,
                                    Quote<Swap>
                            >,
                            TypeList<>,
                            double
                    >
            >(),
            ""
    );

    //
    static_assert(
            is_same<
                    TypeList<double>,
                    ApplyT<
                            Compose<
                                    Quote<FlattenTypeListWithUnpack>,
                                    Quote<Swap>
                            >,
                            TypeList<>,
                            double
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

