#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"
#include "rocky/et/PlaceHolderDef.h"


TEST_CASE("pre-order traversal", "[et]")
{
    expression_traversal<pre_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    runner.go(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    runner.go(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("in-order traversal", "[et]")
{
    expression_traversal<in_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    runner.go(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    runner.go(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("post-order traversal", "[et]")
{
    expression_traversal<post_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    runner.go(expr, [](auto & node, auto & context) { });

    // rvalue expression object
    runner.go(_1 + 10, [](auto && node, auto && context) { });

    int nodeCnt = 0;
    runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}
