#include "../../catch.hpp"

#include "rocky/math/calc/Calculator.h"
#include "rocky/math/calc/Utility.h"


TEST_CASE("calculator expr", "[math]")
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
