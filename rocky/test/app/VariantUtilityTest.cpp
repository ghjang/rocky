#include "../catch.hpp"

#include "rocky/app/VariantUtility.h"


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


TEST_CASE("ToVariantType", "[VariantUtility]")
{
    using std::is_same;
    using std::tuple;
    using boost::variant;

    using tuple_t = tuple<char, int, double>;
    using variant_t = variant<char, int, double>;
    static_assert(
            is_same<variant_t, ToVariantTypeT<tuple_t>>(),
            "converted tuple_t shoulb be same as variant_t."
    );
}

TEST_CASE("ToTupleType", "[VariantUtility]")
{
    using std::is_same;
    using std::tuple;
    using boost::variant;

    using variant_t = variant<char, int, double>;
    using tuple_t = tuple<char, int, double>;
    static_assert(
            is_same<tuple_t, typename ToTupleType<variant_t>::type>(),
            "converted variant_t shoulb be same as tuple_t."
    );
}

TEST_CASE("MakeVariant", "[VariantUtility]")
{
    using boost::apply_visitor;

    auto e0 = MakeVariant(1);
    auto e1 = MakeVariant(1);
    REQUIRE(apply_visitor(IsEqual(), e0, e1));

    auto e2 = MakeVariant('a');
    REQUIRE(!apply_visitor(IsEqual(), e0, e2));

    auto e3 = MakeVariant("abc");
    auto e4 = MakeVariant(L"abc");
    REQUIRE(!apply_visitor(IsEqual(), e3, e4));

    auto e5 = MakeVariant("abc");
    auto e6 = MakeVariant("ABC");
    REQUIRE(apply_visitor(IsEqual(), e3, e5));
    REQUIRE(!apply_visitor(IsEqual(), e3, e6));
}

TEST_CASE("MakeVariantVector, basic", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;
    using boost::apply_visitor;

    auto && vv = MakeVariantVector(1, 1.0, 'a');
    using result_t = vector<variant<int, double, char>>;
    static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
    REQUIRE(vv.size() == 3);

    auto && e0 = MakeVariant(1);
    auto && e1 = MakeVariant(1.0);
    auto && e2 = MakeVariant('a');
    REQUIRE(apply_visitor(IsEqual(), vv[0], e0));
    REQUIRE(apply_visitor(IsEqual(), vv[1], e1));
    REQUIRE(apply_visitor(IsEqual(), vv[2], e2));
}

TEST_CASE("MakeVariantVector, duplicate parameter types", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;
    using boost::apply_visitor;

    auto && vv = MakeVariantVector(1, 1.0, 'a', 2, 'b');
    using result_t = vector<variant<int, double, char>>;
    static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
    REQUIRE(vv.size() == 5);

    auto && e0 = MakeVariant(1);
    auto && e1 = MakeVariant(1.0);
    auto && e2 = MakeVariant('a');
    auto && e3 = MakeVariant(2);
    auto && e4 = MakeVariant('b');
    REQUIRE(apply_visitor(IsEqual(), vv[0], e0));
    REQUIRE(apply_visitor(IsEqual(), vv[1], e1));
    REQUIRE(apply_visitor(IsEqual(), vv[2], e2));
    REQUIRE(apply_visitor(IsEqual(), vv[3], e3));
    REQUIRE(apply_visitor(IsEqual(), vv[4], e4));
}

TEST_CASE("MakeVariantVector, char * types", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;
    using boost::apply_visitor;

    {
        auto && vv = MakeVariantVector(1, 1.0, 'a', 2, 'b', "abc");
        using result_t = vector<variant<int, double, char, std::string>>;
        static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
        REQUIRE(vv.size() == 6);

        auto && e0 = MakeVariant(1);
        auto && e1 = MakeVariant(1.0);
        auto && e2 = MakeVariant('a');
        auto && e3 = MakeVariant(2);
        auto && e4 = MakeVariant('b');
        auto && e5 = MakeVariant("abc");
        REQUIRE(apply_visitor(IsEqual(), vv[0], e0));
        REQUIRE(apply_visitor(IsEqual(), vv[1], e1));
        REQUIRE(apply_visitor(IsEqual(), vv[2], e2));
        REQUIRE(apply_visitor(IsEqual(), vv[3], e3));
        REQUIRE(apply_visitor(IsEqual(), vv[4], e4));
        REQUIRE(apply_visitor(IsEqual(), vv[5], e5));
    }

    {
        auto && vv = MakeVariantVector(1, 1.0, 'a', 2, 'b', "abc", float(3), L"zxy", "zxy");
        using result_t = vector<variant<int, double, char, std::string, float, std::wstring>>;
        static_assert(is_same<decay_t<decltype(vv)>, result_t>(), "vv's type should be result_t.");
        REQUIRE(vv.size() == 9);

        auto && e0 = MakeVariant(1);
        auto && e1 = MakeVariant(1.0);
        auto && e2 = MakeVariant('a');
        auto && e3 = MakeVariant(2);
        auto && e4 = MakeVariant('b');
        auto && e5 = MakeVariant("abc");
        auto && e6 = MakeVariant(float(3));
        auto && e7 = MakeVariant(L"zxy");
        REQUIRE(apply_visitor(IsEqual(), vv[0], e0));
        REQUIRE(apply_visitor(IsEqual(), vv[1], e1));
        REQUIRE(apply_visitor(IsEqual(), vv[2], e2));
        REQUIRE(apply_visitor(IsEqual(), vv[3], e3));
        REQUIRE(apply_visitor(IsEqual(), vv[4], e4));
        REQUIRE(apply_visitor(IsEqual(), vv[5], e5));
        REQUIRE(apply_visitor(IsEqual(), vv[6], e6));
        REQUIRE(apply_visitor(IsEqual(), vv[7], e7));

        REQUIRE(!apply_visitor(IsEqual(), vv[1], e0));
        REQUIRE(!apply_visitor(IsEqual(), vv[8], e7));
    }
}

