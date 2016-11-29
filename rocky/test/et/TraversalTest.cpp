#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"
#include "rocky/et/PlaceHolderDef.h"


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
