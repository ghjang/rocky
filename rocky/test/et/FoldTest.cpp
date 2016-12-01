#include "../catch.hpp"

#include <numeric>
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


template <typename... T>
auto sum_impl_fold(T... args)
{
    return (... + args);
}

template <typename T, std::size_t n, std::size_t... i>
auto sum_impl(std::array<T, n> & a, std::index_sequence<i...>)
{
    return sum_impl_fold(std::get<i>(a)...);
}

template <typename T, std::size_t n>
auto sum(std::array<T, n> & a)
{
    return sum_impl(a, std::make_index_sequence<n>{});
}

TEST_CASE("max function argument count", "[et]")
{
    // NOTE: compile error
    //       clang: error: unable to execute command: Segmentation fault: 11
    //       clang: error: clang frontend command failed due to signal (use -v to see invocation)
    //       Apple LLVM version 8.0.0 (clang-800.0.38)
    //       Target: x86_64-apple-darwin16.1.0
    //std::array<int, 1024 * 2 * 2 * 2 * 2 * 2> a;

    // NOTE: This works. But it takes too much time to wait.
    //std::array<int, 1024 * 2 * 2 * 2 * 2> a;

    std::array<int, 100> a;
    std::iota(a.begin(), a.end(), 1);

    /*
    std::cout << "array size: " << a.size() << '\n'
              << "sum: " << sum(a) << '\n';
    */

    REQUIRE(sum(a) == 5050);
}
