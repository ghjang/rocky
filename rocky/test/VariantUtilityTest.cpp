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

TEST_CASE("CharPtrTypeToStrType", "[VariantUtility]")
{
    using std::is_same;

    {
        char a[] = "abc";
        static_assert(is_same<decltype(a), char [4]>(), "");
        static_assert(is_same<std::string, typename CharPtrTypeToStrType<decltype(a)>::type>(), "");

        wchar_t wa[] = L"abc";
        static_assert(is_same<decltype(wa), wchar_t [4]>(), "");
        static_assert(is_same<std::wstring, typename CharPtrTypeToStrType<decltype(wa)>::type>(), "");
    }

    {
        using str_t = decltype("abc");
        static_assert(is_same<str_t, char const (&)[4]>(), "");
        static_assert(is_same<std::string, typename CharPtrTypeToStrType<str_t>::type>(), "");

        using wstr_t = decltype(L"abc");
        static_assert(is_same<wstr_t, wchar_t const (&)[4]>(), "");
        static_assert(is_same<std::wstring, typename CharPtrTypeToStrType<wstr_t>::type>(), "");
    }

    {
        char const * str = "abc";
        static_assert(is_same<decltype(str), char const *>(), "");
        static_assert(is_same<std::string, typename CharPtrTypeToStrType<decltype(str)>::type>(), "");

        wchar_t const * wstr = L"abc";
        static_assert(is_same<decltype(wstr), wchar_t const *>(), "");
        static_assert(is_same<std::wstring, typename CharPtrTypeToStrType<decltype(wstr)>::type>(), "");
    }

    {
        char a[] = "abc";
        char * pa = a;
        static_assert(is_same<decltype(pa), char *>(), "");
        static_assert(is_same<std::string, typename CharPtrTypeToStrType<decltype(pa)>::type>(), "");

        wchar_t wa[] = L"abc";
        wchar_t * pwa = wa;
        static_assert(is_same<decltype(pwa), wchar_t *>(), "");
        static_assert(is_same<std::wstring, typename CharPtrTypeToStrType<decltype(pwa)>::type>(), "");
    }
}

TEST_CASE("MakeVariant", "[VariantUtility]")
{
    auto e0 = MakeVariant(1);
    auto e1 = MakeVariant(1);
    REQUIRE(boost::apply_visitor(IsEqual(), e0, e1));

    auto e2 = MakeVariant('a');
    REQUIRE(!boost::apply_visitor(IsEqual(), e0, e2));

    auto e3 = MakeVariant("abc");
    auto e4 = MakeVariant(L"abc");
    REQUIRE(!boost::apply_visitor(IsEqual(), e3, e4));

    auto e5 = MakeVariant("abc");
    auto e6 = MakeVariant("ABC");
    REQUIRE(boost::apply_visitor(IsEqual(), e3, e5));
    REQUIRE(!boost::apply_visitor(IsEqual(), e3, e6));
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

TEST_CASE("MakeVariantVector, char * types", "[VariantUtility]")
{
    using std::is_same;
    using std::decay_t;
    using std::vector;
    using boost::variant;

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
        REQUIRE(boost::apply_visitor(IsEqual(), vv[0], e0));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[1], e1));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[2], e2));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[3], e3));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[4], e4));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[5], e5));
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
        REQUIRE(boost::apply_visitor(IsEqual(), vv[0], e0));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[1], e1));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[2], e2));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[3], e3));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[4], e4));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[5], e5));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[6], e6));
        REQUIRE(boost::apply_visitor(IsEqual(), vv[7], e7));

        REQUIRE(!boost::apply_visitor(IsEqual(), vv[1], e0));
        REQUIRE(!boost::apply_visitor(IsEqual(), vv[8], e7));
    }
}

