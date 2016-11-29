#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Print.h"
#include "rocky/et/PlaceHolderDef.h"


struct NotPrintableLocalStructType
{ };

TEST_CASE("print expression tree structure", "[et]")
{
    std::ostringstream oss;

    std::ostream & out = oss;
    //std::ostream & out = std::cout;

    auto expr = _1 + 10;
    print_tree(expr, out);

    out << '\n';

    print_tree((_1 + 10) * (_2 - 20), out);

    out << '\n';

    print_tree(_1 + "C String", out);

    out << '\n';

    std::string s = "C++ String";
    print_tree(_1 + s, out);

    out << '\n';

    NotPrintableLocalStructType np;
    print_tree(_1 + np, out);

    out << '\n';
    print_tree(_2 + NotPrintableLocalStructType{}, out);

    out << '\n';
    print_tree(++_1 + _2--, out);
}

TEST_CASE("print expression to string", "[et]")
{
    std::ostringstream oss;

    auto expr = _1 + 1;
    print_tree_to_str(expr, oss);
    REQUIRE(oss.str() == "(_1 + 1)");

    auto expr1 = (_1 + 1) * (_2 + 2);
    oss.str("");
    print_tree_to_str(expr1, oss);
    REQUIRE(oss.str() == "((_1 + 1) * (_2 + 2))");

    auto expr2 = 1 * _2 + 2;
    oss.str("");
    print_tree_to_str(expr2, oss);
    REQUIRE(oss.str() == "((1 * _2) + 2)");

    auto expr3 = _1 + 1 * _2;
    oss.str("");
    print_tree_to_str(expr3, oss);
    REQUIRE(oss.str() == "(_1 + (1 * _2))");

    auto expr4 = _1 + 1 * _2 - 2;
    oss.str("");
    print_tree_to_str(expr4, oss);
    REQUIRE(oss.str() == "((_1 + (1 * _2)) - 2)");

    auto expr5 = ++_1 + _2--;
    oss.str("");
    print_tree_to_str(expr5, oss);
    REQUIRE(oss.str() == "((++_1) + (_2--))");
}

TEST_CASE("expression tree to graphviz DOT output", "[et]")
{
    std::ostringstream oss;

    std::ostream & out = oss;
    //std::ostream & out = std::cout;

    auto expr =(_1 + 100) * (_2 - 200) / _3;
    print_tree_to_graphviz_dot(expr, out);

    out << '\n';

    auto expr1 = ++_1 + _2--;
    print_tree_to_graphviz_dot(expr1, out);
}
