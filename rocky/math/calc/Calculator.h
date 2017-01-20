#ifndef ROCKY_MATH_CALC_CALCULATOR_H
#define ROCKY_MATH_CALC_CALCULATOR_H


#include <boost/spirit/include/qi.hpp>


namespace rocky::math::calc
{
    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, qi::ascii::space_type>
    {
        calculator() : calculator::base_type(expr_)
        {
            using qi::uint_;

            expr_ = term_
                        >> *(
                                '+' >> term_
                            |   '-' >> term_
                            );

            term_ = factor_
                        >> *(
                                '*' >> factor_
                            |   '/' >> factor_
                            );

            factor_ = power_
                        | ('-' >> power_)
                        | ('+' >> power_);

            power_ = base_
                        >> *(
                                '^' >> expr_
                            );

            base_ = uint_
                        | '(' >> expr_ >> ')';
        }

        qi::rule<Iterator, qi::ascii::space_type> expr_;
        qi::rule<Iterator, qi::ascii::space_type> term_;
        qi::rule<Iterator, qi::ascii::space_type> factor_;
        qi::rule<Iterator, qi::ascii::space_type> power_;
        qi::rule<Iterator, qi::ascii::space_type> base_;
    };
} // namespace rocky::math::calc


#endif // ROCKY_MATH_CALC_CALCULATOR_H
