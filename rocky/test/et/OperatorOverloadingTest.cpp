#include "../catch.hpp"

#include <string>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h" 


TEST_CASE("size of operator overloading", "[et]")
{
    REQUIRE(29 == BINARY_OPERATOR_TUPLES_size);
    REQUIRE(9 == UNARY_OPERATOR_TUPLES_size);
}

TEST_CASE("operator overloading helper macro", "[et]")
{
    // for binary operator
    {
        std::string name = BINARY_OPERATOR_name_str(BINARY_OPERATOR_TUPLES_at(0));
        std::string symbol = BINARY_OPERATOR_symbol_str(BINARY_OPERATOR_TUPLES_at(0));
        REQUIRE("addition" == name);
        REQUIRE("+" == symbol);
    }

    // for unary operator
    {
        std::string name = UNARY_OPERATOR_name_str(UNARY_OPERATOR_TUPLES_at(0));
        std::string symbol = UNARY_OPERATOR_symbol_str(UNARY_OPERATOR_TUPLES_at(0));
        REQUIRE("prefix_increment" == name);
        REQUIRE("++" == symbol);
    }
}

TEST_CASE("prefix unary operator overloading", "[et]")
{
    auto expr = ++_1;
    REQUIRE(expr(10) == 11);

    auto expr1 = -_1;
    REQUIRE(expr1(10) == -10);

    auto expr2 = ++_1 + --_2;
    REQUIRE(expr2(10, 20) == 30);
}

TEST_CASE("postfix unary operator overloading", "[et]")
{
    auto expr = _1++;
    REQUIRE(expr(10) == 10);

    auto expr2 = ++_1 + _2--;
    REQUIRE(expr2(10, 20) == 31);
}
