#include "../catch.hpp"

#include "rocky/base/TypeUtility.h"


TEST_CASE("basic type wrapping as a value", "[TypeUtility]")
{
    using std::is_same;

    static_assert(is_same<Identity<int> const, decltype(type_c<int>)>(), "Identity<int> const == decltype(type_c<int>)");
}

TEST_CASE("NegatePrdicate", "[TypeUtility]")
{
    using std::is_integral;

    static_assert(is_integral<int>(), "");
    static_assert(!ApplyT<NegatePredicate<Quote<is_integral>>, int>(), "");
}

TEST_CASE("CharTypeToStringType", "[TypeUtility]")
{
    using std::is_same;

    {
        // NOTE: arr itself is rvalue.
        char arr[4] = "abc";
        REQUIRE(static_cast<void *>(&arr) == static_cast<void *>(&(arr[0])));
    }

    {
        char a[] = "abc";
        static_assert(is_same<decltype(a), char [4]>(), "");
        static_assert(is_same<std::string, typename CharTypeToStringType<decltype(a)>::type>(), "");

        wchar_t wa[] = L"abc";
        static_assert(is_same<decltype(wa), wchar_t [4]>(), "");
        static_assert(is_same<std::wstring, typename CharTypeToStringType<decltype(wa)>::type>(), "");
    }

    {
        // can have the address for the "abc" string literal.
        char const (* pc)[4] = &"abc";
        static_assert(is_same<char const (*) [4], decltype(pc)>(), "");

        // array-to-pointer decay
        char const * dpc = "abc";
        static_assert(is_same<char const *, decltype(dpc)>(), "");

        // NOTE: "abc" string literal is lvalue.
        using str_t = decltype("abc");
        static_assert(is_same<str_t, char const (&)[4]>(), "");
        static_assert(is_same<std::string, typename CharTypeToStringType<str_t>::type>(), "");

        using wstr_t = decltype(L"abc");
        static_assert(is_same<wstr_t, wchar_t const (&)[4]>(), "");
        static_assert(is_same<std::wstring, typename CharTypeToStringType<wstr_t>::type>(), "");
    }

    {
        char const * str = "abc";
        static_assert(is_same<decltype(str), char const *>(), "");
        static_assert(is_same<std::string, typename CharTypeToStringType<decltype(str)>::type>(), "");

        wchar_t const * wstr = L"abc";
        static_assert(is_same<decltype(wstr), wchar_t const *>(), "");
        static_assert(is_same<std::wstring, typename CharTypeToStringType<decltype(wstr)>::type>(), "");
    }

    {
        char a[] = "abc";
        char * pa = a;
        static_assert(is_same<decltype(pa), char *>(), "");
        static_assert(is_same<std::string, typename CharTypeToStringType<decltype(pa)>::type>(), "");

        wchar_t wa[] = L"abc";
        wchar_t * pwa = wa;
        static_assert(is_same<decltype(pwa), wchar_t *>(), "");
        static_assert(is_same<std::wstring, typename CharTypeToStringType<decltype(pwa)>::type>(), "");
    }
}

TEST_CASE("Bind1st", "[TypeUtility]")
{
    using std::is_same;

    static_assert(ApplyT<Bind1st<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<Bind1st<Quote<is_same>, char>, int>(), "");
}

TEST_CASE("Bind2nd", "[TypeUtility]")
{
    using std::is_same;

    static_assert(ApplyT<Bind2nd<Quote<is_same>, char>, char>(), "");
    static_assert(!ApplyT<Bind2nd<Quote<is_same>, char>, int>(), "");
}

