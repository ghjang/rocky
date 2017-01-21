#include "../../catch.hpp"

#include <utility>

#include "rocky/math/calc/Calculator.h"
#include "rocky/math/calc/Utility.h"


TEST_CASE("calculator expr match", "[math]")
{
    using tools::test_phrase_parser;
    using rocky::math::calc::calculator;

    calculator<std::string::iterator> calc_;

    std::string successExprs[] = {
          "10"
        , "-10"
        , "+10"
        , "10^2"
        , "10^-2"
        , "(1 + (2 * 2))^2"
        , "10 + 20"
        , "10 + +20"
        , "10 + -20"
        , "10 * -(20 + 30)"
        , "10 * (-20 + 30)"
        , "10^2 * (-20 + 30)"
        , "10 * (-20 + 30) ^ 2"
        , "10 * (-20 + 30) ^ 2 ^ 3"
        , "10 * -(-20^2 + 30) ^ 2 ^ 3"
        , "10 * -(-20^2 + 30) ^ 2 ^ 3^(1)"
        , "10 * -(-20^2 + 30) ^ 2 ^ 3^(1*1)"
    };

    for (auto & s : successExprs) {
        REQUIRE(test_phrase_parser(s, calc_));
    }

    std::string failExprs[] = {
          "10 20"
        , "--10"
        , "---10"
        , "- --10"
        , "10^^2"
    };

    for (auto & s : failExprs) {
        REQUIRE_FALSE(test_phrase_parser(s, calc_));
    }
}

TEST_CASE("calculator expr eval", "[math]")
{
    namespace qi = boost::spirit::qi;
    using namespace rocky::math::calc;

    vmachine vm;
    calculator<std::string::iterator> calc_;

    std::pair<std::string, int> exprAndResultPairs[] = {
          { "10",               10  }
        , { "-10",              -10 }
        , { "+10",              10  }
        , { "10+10",            20  }
        , { "10-20",            -10 }
        , { "10*10",            100 }
        , { "10/2",             5   }
        , { "10*(2+3)",         50  }
        , { "10*(-2+3)",        10  }
        , { "10*(-2+3)+5",      15  }
        , { "10*(-2+3)-5",      5   }
        , { "10*(-2+3)/2",      5   }
    };

    for (auto & pair : exprAndResultPairs) {
        // building the AST
        ast::expression expr;
        auto begin = pair.first.begin();
        auto end = pair.first.end();
        REQUIRE(qi::phrase_parse(begin, end, calc_, qi::ascii::space, expr));
        REQUIRE(begin == end);

        // compile & execute
        std::vector<int> code;
        compiler compile(code);
        compile(expr);
        vm.execute(code);
        REQUIRE(vm.top() == pair.second);
    }
}
