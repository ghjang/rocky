#include "../catch.hpp"

#include <iostream>

#include "rocky/et/Fold.h"
#include "rocky/et/Print.h"



TEST_CASE("fold addition", "[et]")
{
    // fold left
    auto result = foldl(
                        [](int acc, int n) { return acc + n; }, // binary op
                        0,                                      // init
                        1, 2, 3, 4, 5                           // sequence
                  );
    REQUIRE(15 == result);

    // fold right
    auto result1 = foldr(
                        [](int n, int acc) { return n + acc; }, // binary op
                        0,                                      // init
                        1, 2, 3, 4, 5                           // sequence
                   );
    REQUIRE(15 == result1);
}

TEST_CASE("fold subtraction", "[et]")
{
    // fold left
    auto result = foldl(
                        [](int acc, int n) { return acc - n; }, // binary op
                        0,                                      // init
                        1, 2, 3, 4, 5                           // sequence
                  );
    REQUIRE(-15 == result);

    // fold right
    auto result1 = foldr(
                        [](int n, int acc) { return n - acc; }, // binary op
                        0,                                      // init
                        1, 2, 3, 4, 5                           // sequence
                   );
    REQUIRE(3 == result1);
}

TEST_CASE("fold expression tree", "[et]")
{
    std::ostringstream oss;
    std::ostream & out = oss;
    //std::ostream & out = std::cout;

    auto lexpr = foldl_expr(1, 2, 3, 4, 5);
    print_tree_to_graphviz_dot(lexpr, out);

    auto rexpr = foldr_expr(1, 2, 3, 4, 5);
    print_tree_to_graphviz_dot(rexpr, out);
}


struct to_str
{
    // binary op for foldr.
    // print them to string in reverse order.
    template <typename Lhs, typename Rhs>
    auto operator () (Lhs && l, Rhs && acc)
    {
        std::ostringstream oss;
        oss << std::forward<Rhs>(acc)
            << ", "
            << std::forward<Lhs>(l);
        return oss.str();
    }
};

TEST_CASE("arguments to reversed order string", "[et]")
{
    auto s = foldr(
                to_str{},               // binary op
                "init",                 // init
                1, 'F', "abc", 2.2      // sequence
             );
    REQUIRE(s == "init, 2.2, abc, F, 1");
}
