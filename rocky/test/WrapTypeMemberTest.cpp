#include "catch.hpp"

#include "rocky/WrapTypeMember.h"

#include <type_traits>

#include "rocky/HasTypeMember.h"


TEST_CASE("Wrapping as type member", "[WrapTypeMember]")
{
    using std::is_same;

    struct A { };
    struct B { using type = int; };

    using WrappedA = WrapAsTypeMember<A>;
    static_assert(HasTypeMember<WrappedA>::value, "WrappedA should have 'type' member.");
    static_assert(is_same<WrappedA::type, A>::value, "WrappedA::type should be A.");

    using WrappedB = WrapAsTypeMember<B>;
    static_assert(HasTypeMember<WrappedB>::value, "WrappedB should have 'type' member.");
    static_assert(is_same<WrappedB::type, B>::value, "WrappedB::type should be B.");
    static_assert(is_same<WrappedB::type::type, int>::value, "WrappedB::type::type should be int.");
}

