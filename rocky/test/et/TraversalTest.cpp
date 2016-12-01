#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"
#include "rocky/et/PlaceHolderDef.h"


TEST_CASE("pre-order traversal", "[et]")
{
    // NOTE: empty_traversal_context is the default traversal context.
    //       Thus, the callbacks should not specify the second argument
    //       for receving context info.
    expression_traversal<pre_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    //runner.go(expr, [](auto & node, auto & context) { });
    runner.go(expr, [](auto & node) { });

    // rvalue expression object
    //runner.go(_1 + 10, [](auto && node, auto && context) { });
    runner.go(_1 + 10, [](auto && node) { });

    int nodeCnt = 0;
    //runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    runner.go(_1 + 10, [&nodeCnt](auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("in-order traversal", "[et]")
{
    // NOTE: empty_traversal_context is the default traversal context.
    //       Thus, the callbacks should not specify the second argument
    //       for receving context info.
    expression_traversal<in_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    //runner.go(expr, [](auto & node, auto & context) { });
    runner.go(expr, [](auto & node) { });

    // rvalue expression object
    //runner.go(_1 + 10, [](auto && node, auto && context) { });
    runner.go(_1 + 10, [](auto && node) { });

    int nodeCnt = 0;
    //runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    runner.go(_1 + 10, [&nodeCnt](auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}

TEST_CASE("post-order traversal", "[et]")
{
    // NOTE: empty_traversal_context is the default traversal context.
    //       Thus, the callbacks should not specify the second argument
    //       for receving context info.
    expression_traversal<post_order> runner;

    // lvalue expression object
    auto expr = _1 + 10;
    //runner.go(expr, [](auto & node, auto & context) { });
    runner.go(expr, [](auto & node) { });

    // rvalue expression object
    //runner.go(_1 + 10, [](auto && node, auto && context) { });
    runner.go(_1 + 10, [](auto && node) { });

    int nodeCnt = 0;
    //runner.go(_1 + 10, [&nodeCnt](auto &&, auto &&){ ++nodeCnt; });
    runner.go(_1 + 10, [&nodeCnt](auto &&){ ++nodeCnt; });
    REQUIRE(3 == nodeCnt);
}
