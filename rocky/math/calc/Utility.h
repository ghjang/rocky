#ifndef ROCKY_MATH_CALC_UTILITY_H
#define ROCKY_MATH_CALC_UTILITY_H


#include <string>
#include <iostream>
#include <fstream>

#include <boost/type_index.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>


inline std::string read_from_file(char const* infile)
{
    std::ifstream instream(infile);
    if (!instream.is_open()) {
        std::cerr << "Couldn't open file: " << infile << std::endl;
        exit(-1);
    }
    instream.unsetf(std::ios::skipws);      // No white space skipping!
    return std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                       std::istreambuf_iterator<char>());
}


namespace tools
{
    namespace spirit = boost::spirit;

    template <typename Expr, typename Iterator = spirit::unused_type>
    struct attribute_of_parser
    {
        using parser_expression_type = typename spirit::result_of::compile<
                                                        spirit::qi::domain, Expr
                                                    >::type;

        using type = typename spirit::traits::attribute_of<
                                    parser_expression_type, spirit::unused_type, Iterator
                                >::type;
    };

    template <typename T>
    void display_attribute_of_parser(T const &) 
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        BOOST_SPIRIT_ASSERT_MATCH(spirit::qi::domain, T);

        using type = typename attribute_of_parser<T>::type;
        std::cout << boost::typeindex::type_id<type>().pretty_name() << '\n';
    }

    template <typename T>
    void display_attribute_of_parser(std::ostream& os, T const &) 
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        BOOST_SPIRIT_ASSERT_MATCH(spirit::qi::domain, T);

        using type = typename attribute_of_parser<T>::type;
        os << boost::typeindex::type_id<type>().pretty_name() << '\n';
    }

    template <typename Parser>
    bool test_parser(std::string & s, Parser const& p, bool fullMatch = true)
    {
        namespace qi = boost::spirit::qi;
        auto begin = s.begin();
        auto end = s.end();
        bool r = qi::parse(begin, end, p);
        return (r && (!fullMatch || (begin == end)));
    }

    template <typename Parser>
    bool test_phrase_parser(std::string & s, Parser const& p, bool fullMatch = true)
    {
        namespace qi = boost::spirit::qi;
        auto begin = s.begin();
        auto end = s.end();
        bool r = qi::phrase_parse(begin, end, p, qi::ascii::space);
        return (r && (!fullMatch || (begin == end)));
    }

    template <typename Parser, typename Attr>
    bool test_parser_attr(std::string & s, Parser const& p, Attr & a, bool fullMatch = true)
    {
        namespace qi = boost::spirit::qi;
        auto begin = s.begin();
        auto end = s.end();
        bool r = qi::parse(begin, end, p, a);
        return (r && (!fullMatch || (begin == end)));
    }

    template <typename Parser, typename Attr>
    bool test_phrase_parser_attr(std::string & s, Parser const& p, Attr & a, bool fullMatch = true)
    {
        namespace qi = boost::spirit::qi;
        auto begin = s.begin();
        auto end = s.end();
        bool r = qi::phrase_parse(begin, end, p, qi::ascii::space, a);
        return (r && (!fullMatch || (begin == end)));
    }

    template <typename G, typename... T>
    bool test_generator_attr(std::string const& expected, G const& g, T const&... attr)
    {
        std::string s;
        std::back_insert_iterator<std::string> out(s);
        bool r = boost::spirit::karma::generate(out, g, attr...);
        if (r && s == expected) {
            return true;
        }
        std::cout << "<-- test_generator_attr failed -->\n"
                  << "r: " << r << '\n'
                  << "s: " << s << '\n'
                  << "expected: " << expected << '\n';
        return false;
    }

    template <typename G, typename... T>
    bool test_fail_generator_attr(std::string const& expected, G const& g, T const&... attr)
    {
        std::string s;
        std::back_insert_iterator<std::string> out(s);
        bool r = boost::spirit::karma::generate(out, g, attr...);
        if (r && s == expected) {
            std::cout << "<-- test_fail_generator_attr failed -->\n"
                      << "r: " << r << '\n'
                      << "s: " << s << '\n'
                      << "expected: " << expected << '\n';
            return false;
        }
        return true;
    }

    template <typename G, typename Delimiter, typename T>
    void test_generator_attr_delim(std::string const& expected, G const& g, Delimiter const& d, T const& attr)
    {
        std::string s;
        std::back_insert_iterator<std::string> out(s);
        return (boost::spirit::karma::generate_delimited(out, g, d, attr) && s == expected);
    }
} // namespace tools


#endif // ROCKY_MATH_CALC_UTILITY_H
