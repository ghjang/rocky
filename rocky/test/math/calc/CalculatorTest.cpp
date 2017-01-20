#include "../../catch.hpp"

#include "rocky/math/calc/Calculator.h"


TEST_CASE("calculator", "[math]")
{
    namespace qi = boost::spirit::qi;
    using rocky::math::calc::calculator;

    std::string exprStr = "10 * (-20 + 30)";
    
    calculator<std::string::iterator> calc_;

    auto begin = exprStr.begin();
    auto end = exprStr.end();
    bool r = qi::phrase_parse(begin, end, calc_, qi::ascii::space);
    REQUIRE(r);
    REQUIRE(begin == end);
}
