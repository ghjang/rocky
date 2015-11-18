#include "catch.hpp"

#include "rocky/HasMember.h"


TEST_CASE("class without 'type' member", "[HasMember]")
{
    static_assert(!HasTypeMember<int>::value, "int has no type member.");

    struct S { };
    static_assert(!HasTypeMember<S>::value, "struct S has no type member.");
}

TEST_CASE("class with 'type' member", "[HasMember]")
{
    struct S
    {
        using type = int;
    };
    static_assert(HasTypeMember<S>::value, "struct S has type member.");

    static_assert(HasTypeMember<std::is_same<int, int>>::value, "std::is_same<int, int> has type member.");

    //TODO: add support for template template parameter if possible.
    //static_assert(HasTypeMember<std::is_same>::value, "std::is_same has type member.");
}

