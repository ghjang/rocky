#include "../catch.hpp"

#include "rocky/meta/MultipleInheritance.h"

#include <type_traits>


TEST_CASE("multiple inheritance", "[MultipleInheritance]")
{
    struct A { int a_; };
    struct B { int b_; };
    struct C { int c_; };
    struct D { int d_; };
    using MI = MultipleInheritance<A, B, C>::type;
    static_assert(std::is_base_of<A, MI>(), "A is a base type of MI.");
    static_assert(std::is_base_of<B, MI>(), "B is a base type of MI.");
    static_assert(std::is_base_of<C, MI>(), "C is a base type of MI.");
    static_assert(!std::is_base_of<D, MI>(), "D is not a base type of MI.");
}

