#include "catch.hpp"

#include "rocky/meta/Identity.h"

#include <type_traits>

#include "rocky/meta/HasMember.h"


TEST_CASE("Wrapping as type member", "[Identity]")
{
    using std::is_same;

    struct A { };
    struct B { using type = int; };

    using WrappedA = Identity<A>;
    static_assert(HasTypeMember<WrappedA>(), "WrappedA should have 'type' member.");
    static_assert(is_same<WrappedA::type, A>(), "WrappedA::type should be A.");

    using WrappedB = Identity<B>;
    static_assert(HasTypeMember<WrappedB>(), "WrappedB should have 'type' member.");
    static_assert(is_same<WrappedB::type, B>(), "WrappedB::type should be B.");
    static_assert(is_same<WrappedB::type::type, int>(), "WrappedB::type::type should be int.");
}

TEST_CASE("type_is", "[Identity]")
{
    using std::is_same;

    struct A { };
    struct B { using type = int; };

    using WrappedA = type_is<A>;
    static_assert(HasTypeMember<WrappedA>(), "WrappedA should have 'type' member.");
    static_assert(is_same<WrappedA::type, A>(), "WrappedA::type should be A.");

    using WrappedB = type_is<B>;
    static_assert(HasTypeMember<WrappedB>(), "WrappedB should have 'type' member.");
    static_assert(is_same<WrappedB::type, B>(), "WrappedB::type should be B.");
    static_assert(is_same<WrappedB::type::type, int>(), "WrappedB::type::type should be int.");
}

