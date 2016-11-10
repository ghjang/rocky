#include "../catch.hpp"

#include "rocky/et/ExpressionTemplate.h"

#include <iostream>
#include <sstream>


template <typename T>
struct TD;

TEST_CASE("lambda expression", "[et]")
{
    std::ostringstream oss;

    auto expr = oss << _1;

    expr(1024);
    REQUIRE(oss.str() == "1024");

    auto expr1 = expr << '\n';
    //expr1();

    //auto expr2 = std::cout << _1 << " won.";

    oss.str("");
    auto expr2 = oss << _1 << '.';

    /*
    TD<decltype(expr2)> td;
    expression<
        expression<
            std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>, left_shift,
            const placeholder<1>,
            false,
            false
        >,
        left_shift,
        char,
        false,
        true
    >
    */

    expr2(1024);

    /*
    ////
    callable<
        expression<
            expression<
                std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
                left_shift,
                const placeholder<1>,
                false,
                false
            >,
            left_shift,
            char,
            false,
            true
        >
    >::operator()<std::__1::tuple<int> >

    //
    callable<
        expression<
            expression<
                std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
                left_shift,
                const placeholder<1>,
                false,
                false
            >,
            left_shift,
            char,
            false,
            true
        >
    >::call_impl<
        expression<
            std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char> >,left_shift,
            const placeholder<1>,
            false,
            false
        >,
        char &,
        callable<
            expression<
                expression<
                    std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
                    left_shift,
                    const placeholder<1>,
                    false,
                    false
                >,
                left_shift,
                char,
                false,
                true
            >
        >::context<std::__1::tuple<int>>
    >

    //
    callable<
        expression<
            std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
            left_shift,
            const placeholder<1>,
            false,
            false
        >
    >::operator()<
        callable<
            expression<
                expression<
                    std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
                    left_shift,
                    const placeholder<1>,
                    false,
                    false
                >,
                left_shift,
                char,
                false,
                true
            >
        >::context<std::__1::tuple<int>> &
    >

    //
    callable<
        expression<
            std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char>>,
            left_shift,
            const placeholder<1>,
            false,
            false
        >
    >::operator()<
        std::__1::tuple<
            callable<
                expression<
                    expression<
                        std::__1::basic_ostringstream<
                            char,
                            std::__1::char_traits<char>,
                            std::__1::allocator<char>
                        >,
                        left_shift,
                        const placeholder<1>,
                        false,
                        false
                    >,
                    left_shift,
                    char,
                    false,
                    true
                >
            >::context<std::__1::tuple<int>>
        >
    >
    */

    REQUIRE(oss.str() == "1024.");

    /*
    std::__1::tuple<
        callable<
            expression<
                expression<
                    std::__1::basic_ostringstream<
                        char,
                        std::__1::char_traits<char>,
                        std::__1::allocator<char>
                    >,
                    left_shift,
                    const placeholder<1>,
                    false,
                    false
                >,
                left_shift,
                char,
                false,
                true
            >
        >::dummy_arg,
        int
    >
    */

    /*
    expression<
        std::__1::basic_ostringstream<
            char,
            std::__1::char_traits<char>,
            std::__1::allocator<char>
        >,
        left_shift,
        const placeholder<1>,
        false,
        false
    >::apply<
        std::__1::basic_ostringstream<char, std::__1::char_traits<char>, std::__1::allocator<char> > &,
        callable<
            expression<
                expression<
                    std::__1::basic_ostringstream<
                        char,
                        std::__1::char_traits<char>,
                        std::__1::allocator<char>
                    >,
                    left_shift,
                    const placeholder<1>,
                    false,
                    false
                >,
                left_shift,
                char,
                false,
                true
            >
        >::context<std::__1::tuple<int>> &
    >
    */
}
