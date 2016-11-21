#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"
#include "rocky/et/Print.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <sstream>


TEST_CASE("is_expression meta-function", "[et]")
{
    static_assert(!is_expression<std::decay_t<decltype(_1)>>::value);
    static_assert(is_expression<std::decay_t<decltype(_1 + 1)>>::value);
}

TEST_CASE("is_terminal meta-function", "[et]")
{
    static_assert(is_terminal<std::decay_t<decltype(_1)>>::value);
    static_assert(!is_terminal<std::decay_t<decltype(_1 + 1)>>::value);

    value_holder<true, int> vh{ 1 };
    static_assert(is_terminal<std::decay_t<decltype(vh)>>::value);
}

TEST_CASE("size of operator overloading", "[et]")
{
    REQUIRE(29 == BINARY_OPERATOR_TUPLES_size);
}

TEST_CASE("operator overloading helper macro", "[et]")
{
    std::string name = BINARY_OPERATOR_name_str(BINARY_OPERATOR_TUPLES_at(0));
    std::string symbol = BINARY_OPERATOR_symbol_str(BINARY_OPERATOR_TUPLES_at(0));
    REQUIRE("addition" == name);
    REQUIRE("+" == symbol);
}

TEST_CASE("left shift", "[et]")
{
    std::ostringstream oss;

    auto expr = oss << _1;
    expr(1024);
    REQUIRE(oss.str() == "1024");

    oss.str("");
    auto expr2 = oss << _1 << " won.";
    expr2(1024);
    REQUIRE(oss.str() == "1024 won.");

    oss.str("");
    auto expr3 = oss << _1 << '.';
    expr3(1024);
    REQUIRE(oss.str() == "1024.");

    oss.str("");
    auto expr4 = oss << _2 << ", " << _1 << ".";
    expr4(10, 24);
    REQUIRE(oss.str() == "24, 10.");

    oss.str("");
    std::vector<int> v{ 10, 20, 30, 40, 50 };
    std::for_each(v.begin(), v.end(), oss << _1 << ',');
    REQUIRE(oss.str() == "10,20,30,40,50,");
    oss.str("");
    std::for_each(v.begin(), v.end(), oss << _1 << ", ");
    REQUIRE(oss.str() == "10, 20, 30, 40, 50, ");
    oss.str("");
    std::for_each(v.begin(), v.end(), oss << _1 << ',' << _1 << ", ");
    REQUIRE(oss.str() == "10,10, 20,20, 30,30, 40,40, 50,50, ");

    oss.str("");
    auto expr5 = _1 << 1;
    auto expr6 = oss << expr5;  // NOTE: expr5 is evaluated first.
    expr6(10);                  // 10 * 2 == 10 << 1
    REQUIRE(oss.str() == "20");

    oss.str("");
    auto expr7 = oss << (_1 << 2);
    expr7(10);                  // 10 * 2 * 2 == 10 << 2
    REQUIRE(oss.str() == "40");
}

TEST_CASE("assignment lambda expression", "[et]")
{
    std::vector<int> v(5);
    std::iota(v.begin(), v.end(), 1);

    std::for_each(
            v.begin(),
            v.end(),
            _1 += 10
    );

    std::ostringstream oss;
    std::for_each(v.begin(), v.end(), oss << _1 << ", ");

    REQUIRE(oss.str() == "11, 12, 13, 14, 15, ");

    std::iota(v.begin(), v.end(), 1);
    std::for_each(
            v.begin(),
            v.end(),
            (_1 += 10, _1 /= 2) // with comma operator
    );

    oss.str("");
    std::for_each(v.begin(), v.end(), oss << _1 << ", ");

    REQUIRE(oss.str() == "5, 6, 6, 7, 7, ");
}

TEST_CASE("when two sides are both terminal or expression", "[et]")
{
    // two sides are both terminal.
    auto expr = (_1 + _2);

    // two sides for the '-' operator are both expression.
    auto expr1 = (_1 + 10) - (_2 * 10);
    REQUIRE(-180 == expr1(10, 20));

    auto expr2 = (_1 + _2) + (_1 * _2);
    REQUIRE(230 == expr2(10, 20));
}

TEST_CASE("lambda expression", "[et]")
{
    std::vector<int> v(5);
    std::iota(v.begin(), v.end(), 1);

    std::ostringstream oss;

    std::for_each(
        v.begin(),
        v.end(),
        oss << _1 << ", "
    );
    REQUIRE(oss.str() == "1, 2, 3, 4, 5, ");

    oss.str("");
    auto expr = oss << _2 << ", " << _1;
    expr(10, 24);
    REQUIRE(oss.str() == "24, 10");

    REQUIRE(20 == (_1 * 10)(2));
}

TEST_CASE("pre-order traversal", "[et]")
{
    // lvalue expression object
    auto expr = _1 + 10;
    preorder(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    preorder(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    preorder(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("in-order traversal", "[et]")
{
    // lvalue expression object
    auto expr = _1 + 10;
    inorder(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    inorder(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    inorder(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("post-order traversal", "[et]")
{
    // lvalue expression object
    auto expr = _1 + 10;
    postorder(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    postorder(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    postorder(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("print node symbol", "[et]")
{
    auto expr = _1 + 10;
    print_symbol(expr);

    std::cout << '\n';
    
    print_symbol((_1 + 10) * (_2 - 20));
}
