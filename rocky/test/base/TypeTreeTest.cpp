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

TEST_CASE("ForEachChildElementTypeInPostOrder-1", "[TypeTree]")
{
    using tuple_t = std::tuple<char, int, float, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPostOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            tuple_t()
    );

    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == "char");
    REQUIRE(v[1] == "int");
    REQUIRE(v[2] == "float");
    REQUIRE(v[3] == "double");
    REQUIRE(v[4] == "tuple");
}

TEST_CASE("ForEachChildElementTypeInPostOrder-2", "[TypeTree]")
{
    using type_t = std::tuple<char, int, TypeList<float, float>, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPostOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            type_t()
    );

    REQUIRE(v.size() == 7);
    REQUIRE(v[0] == "char");
    REQUIRE(v[1] == "int");
    REQUIRE(v[2] == "float");
    REQUIRE(v[3] == "float");
    REQUIRE(v[4] == "TypeList");
    REQUIRE(v[5] == "double");
    REQUIRE(v[6] == "tuple");
}

TEST_CASE("ForEachChildElementTypeInPostOrder-3", "[TypeTree]")
{
    using type_t = std::tuple<char, int, TypeList<float, std::vector<int>, float>, double>;

    std::vector<std::string> v;

    ForEachChildElementTypeInPostOrder(
            [&v](auto t) {
                using arg_type_t = typename decltype(t)::type;
                v.push_back(name_of<arg_type_t>);
            },
            type_t()
    );

    REQUIRE(v.size() == 11);
    REQUIRE(v[0] == "char");
    REQUIRE(v[1] == "int");
    REQUIRE(v[2] == "float");
    REQUIRE(v[3] == "int");
    REQUIRE(v[4] == "int");
    REQUIRE(v[5] == "allocator");
    REQUIRE(v[6] == "vector");
    REQUIRE(v[7] == "float");
    REQUIRE(v[8] == "TypeList");
    REQUIRE(v[9] == "double");
    REQUIRE(v[10] == "tuple");
}

