#include "catch.hpp"

#include "rocky/VariantUtility.h"


#include <iostream>


namespace
{
    struct IsEqual
            : public boost::static_visitor<bool>
    {
        template <typename T, typename U>
        bool operator () (const T &, const U &) const
        {
            return false; // cannot compare different types
        }

        template <typename T>
        bool operator () (const T & lhs, const T & rhs) const
        {
            return lhs == rhs;
        }
    };
}


TEST_CASE("MakeVariant", "[VariantUtility]")
{
    auto e0 = MakeVariant(1);
    auto e1 = MakeVariant(1);
    REQUIRE(boost::apply_visitor(IsEqual(), e0, e1));

    auto e2 = MakeVariant('a');
    REQUIRE(!boost::apply_visitor(IsEqual(), e0, e2));
}

TEST_CASE("TupleToVariant", "[VariantUtility]")
{
    using std::is_same;
    using std::tuple;
    using boost::variant;

    using tuple_t = tuple<char, int, double>;
    using variant_t = variant<char, int, double>;
    static_assert(
            is_same<variant_t, typename TupleToVariant<tuple_t>::type>(),
            "converted tuple_t shoulb be same as variant_t."
    );
}

TEST_CASE("MakeVariantVector, basic", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;

    auto && vv = MakeVariantVector(1, 1.0, 'a');
    using result_t = vector<variant<int, double, char>>;
    static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
    REQUIRE(vv.size() == 3);

    auto && e0 = MakeVariant(1);
    auto && e1 = MakeVariant(1.0);
    auto && e2 = MakeVariant('a');
    REQUIRE(boost::apply_visitor(IsEqual(), vv[0], e0));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[1], e1));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[2], e2));
}

TEST_CASE("MakeVariantVector, duplicate parameter types", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;

    auto && vv = MakeVariantVector(1, 1.0, 'a', 2, 'b');
    using result_t = vector<variant<int, double, char>>;
    static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
    REQUIRE(vv.size() == 5);

    auto && e0 = MakeVariant(1);
    auto && e1 = MakeVariant(1.0);
    auto && e2 = MakeVariant('a');
    auto && e3 = MakeVariant(2);
    auto && e4 = MakeVariant('b');
    REQUIRE(boost::apply_visitor(IsEqual(), vv[0], e0));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[1], e1));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[2], e2));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[3], e3));
    REQUIRE(boost::apply_visitor(IsEqual(), vv[4], e4));
}

