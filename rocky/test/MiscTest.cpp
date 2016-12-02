#include "catch.hpp"

#include <type_traits>
#include <string>


// in global
using global_t = int;
static_assert(std::is_same<int, global_t>());

namespace my_space
{
    // in a namespace 
    using namespace_t = int;
    static_assert(std::is_same<int, namespace_t>());
} // my_space namespace

template <typename T>
struct my_struct
{
    // in a class
    static_assert(std::is_integral<T>() && sizeof(T) <= 4);

    template <typename U>
    auto func(U u)
    {
        // in a function
        static_assert(std::is_convertible<U, T>());
        T t = u;
        return ++t;
    }
};

TEST_CASE("static_assert", "[misc]")
{
    struct S
    {
        operator int ()
        { return 1024; }
    };

    struct U
    {
        operator std::string ()
        { return "1024"; }
    };

    my_struct<int> s;           // OK
    //my_struct<long long> s1;  // NOT OK
    //my_struct<S> s2;          // NOT OK
    my_struct<int> s3;          // OK
    s3.func(S{});               // OK
    //s3.func(U{});             // NOT OK
}
