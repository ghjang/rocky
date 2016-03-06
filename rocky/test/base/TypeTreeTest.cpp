#include "../catch.hpp"

#include "rocky/base/TypeTree.h"

#include <string>
#include <vector>
#include <iostream>


TEST_CASE("ForEachChildElementTypeInPreOrder-1", "[TypeTree]")
{
    using tuple_t = std::tuple<char, int, float, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPreOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            tuple_t()
    );

    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == "tuple");
    REQUIRE(v[1] == "char");
    REQUIRE(v[2] == "int");
    REQUIRE(v[3] == "float");
    REQUIRE(v[4] == "double");
}

TEST_CASE("ForEachChildElementTypeInPreOrder-2", "[TypeTree]")
{
    using type_t = std::tuple<char, int, TypeList<float, float>, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPreOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            type_t()
    );

    REQUIRE(v.size() == 7);
    REQUIRE(v[0] == "tuple");
    REQUIRE(v[1] == "char");
    REQUIRE(v[2] == "int");
    REQUIRE(v[3] == "TypeList");
    REQUIRE(v[4] == "float");
    REQUIRE(v[5] == "float");
    REQUIRE(v[6] == "double");
}

TEST_CASE("ForEachChildElementTypeInPreOrder-3", "[TypeTree]")
{
    using type_t = std::tuple<char, int, TypeList<float, std::vector<int>, float>, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPreOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            type_t()
    );

    REQUIRE(v.size() == 11);

    REQUIRE(v[0] == "tuple");
    REQUIRE(v[1] == "char");
    REQUIRE(v[2] == "int");
    REQUIRE(v[3] == "TypeList");
    REQUIRE(v[4] == "float");
    REQUIRE(v[5] == "vector");
    REQUIRE(v[6] == "int");
    REQUIRE(v[7] == "allocator");
    REQUIRE(v[8] == "int");
    REQUIRE(v[9] == "float");
    REQUIRE(v[10] == "double");
}

