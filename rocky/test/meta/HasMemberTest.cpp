#include "../catch.hpp"

#include "rocky/meta/HasMember.h"


TEST_CASE("class without 'type' member", "[HasMember]")
{
    static_assert(!HasTypeMember<int>(), "int has no type member.");

    struct S { };
    static_assert(!HasTypeMember<S>(), "struct S has no type member.");
}

TEST_CASE("class with 'type' member", "[HasMember]")
{
    struct S
    {
        using type = int;
    };
    static_assert(HasTypeMember<S>(), "struct S has type member.");

    static_assert(HasTypeMember<std::is_same<int, int>>(), "std::is_same<int, int> has type member.");

    //TODO: add support for template template parameter if possible.
    //static_assert(HasTypeMember<std::is_same>(), "std::is_same has type member.");
}

TEST_CASE("class without 'value' member", "[HasMember]")
{
    static_assert(!HasValueMember<int>(), "int has no value member.");

    struct S { };
    static_assert(!HasValueMember<S>(), "struct S has no value member.");
}

TEST_CASE("class with 'value' member", "[HasMember]")
{
    using std::is_same;
    using std::is_class;

    struct S
    {
        int value;
    };
    static_assert(HasValueMember<S>(), "struct S has value member.");

    static_assert(HasValueMember<is_same<int, int>>(), "std::is_same<int, int> has value member.");

    //TODO: add support for template template parameter if possible.
    //static_assert(HasValueMember<is_same>(), "std::is_same has value member.");
}

