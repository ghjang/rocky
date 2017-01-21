#ifndef ROCKY_MATH_CALC_CALCULATOR_H
#define ROCKY_MATH_CALC_CALCULATOR_H


#include <cmath>
#include <vector>

#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>


namespace rocky::math::calc::ast
{
    struct nil { };
    struct unary;
    struct expression;

    using operand = boost::variant<
                        nil,
                        unsigned int,
                        boost::recursive_wrapper<unary>,
                        boost::recursive_wrapper<expression>
                    >;

    struct unary
    {
        char operator_;
        operand operand_;
    };

    struct operation
    {
        char operator_;
        operand operand_;
    };

    struct expression
    {
        operand first_;
        std::vector<operation> rest_;
    };
} // namespacde rocky::math::calc::ast

BOOST_FUSION_ADAPT_STRUCT(
    rocky::math::calc::ast::unary,
    (char, operator_)
    (rocky::math::calc::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    rocky::math::calc::ast::operation,
    (char, operator_)
    (rocky::math::calc::ast::operand, operand_)
)

BOOST_FUSION_ADAPT_STRUCT(
    rocky::math::calc::ast::expression,
    (rocky::math::calc::ast::operand, first_)
    (std::vector<rocky::math::calc::ast::operation>, rest_)
)


namespace rocky::math::calc
{
    enum byte_code
    {
        op_neg,
        op_add,
        op_sub,
        op_mul,
        op_div,
        op_pow,
        op_int,
    };

    class vmachine
    {
    public:
        vmachine(unsigned stackSize = 4096)
          : stack_(stackSize)
          , stackPtr_(stack_.begin())
        {  }

        int top() const { return stackPtr_[-1]; };
        void execute(std::vector<int> const& code);

    private:
        std::vector<int> stack_;
        std::vector<int>::iterator stackPtr_;
    };

    void vmachine::execute(std::vector<int> const& code)
    {
        std::vector<int>::const_iterator pc = code.begin();
        stackPtr_ = stack_.begin();

        while (pc != code.end())
        {
            switch (*pc++)
            {
                case op_neg:
                    stackPtr_[-1] = -stackPtr_[-1];
                    break;

                case op_add:
                    --stackPtr_;
                    stackPtr_[-1] += stackPtr_[0];
                    break;

                case op_sub:
                    --stackPtr_;
                    stackPtr_[-1] -= stackPtr_[0];
                    break;

                case op_mul:
                    --stackPtr_;
                    stackPtr_[-1] *= stackPtr_[0];
                    break;

                case op_div:
                    --stackPtr_;
                    stackPtr_[-1] /= stackPtr_[0];
                    break;

                case op_pow:
                    --stackPtr_;
                    stackPtr_[-1] = std::pow(stackPtr_[-1], stackPtr_[0]);
                    break;

                case op_int:
                    *stackPtr_++ = *pc++;
                    break;
            }
        }
    }


    struct compiler : boost::static_visitor<>
    {
        std::vector<int>& code_;

        compiler(std::vector<int> & code)
          : code_(code)
        { }

        void operator()(ast::nil) const
        { BOOST_ASSERT(0); }

        void operator()(unsigned int n) const
        {
            code_.push_back(op_int);
            code_.push_back(n);
        }

        void operator()(ast::operation const& x) const
        {
            boost::apply_visitor(*this, x.operand_);
            switch (x.operator_)
            {
                case '+': code_.push_back(op_add); break;
                case '-': code_.push_back(op_sub); break;
                case '*': code_.push_back(op_mul); break;
                case '/': code_.push_back(op_div); break;
                case '^': code_.push_back(op_pow); break;
                default: BOOST_ASSERT(0); break;
            }
        }

        void operator()(ast::unary const& x) const
        {
            boost::apply_visitor(*this, x.operand_);
            switch (x.operator_)
            {
                case '-': code_.push_back(op_neg); break;
                case '+': break;
                default: BOOST_ASSERT(0); break;
            }
        }

        void operator()(ast::expression const& x) const
        {
            boost::apply_visitor(*this, x.first_);
            for (ast::operation const& oper : x.rest_)
            {
                (*this)(oper);
            }
        }
    };


    namespace qi = boost::spirit::qi;

    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, ast::expression(), qi::ascii::space_type>
    {
        calculator() : calculator::base_type(expr_)
        {
            using qi::char_;
            using qi::uint_;
            using qi::attr;

            expr_ = term_
                        >> *(
                                char_('+') >> term_
                            |   char_('-') >> term_
                            );

            term_ = factor_
                        >> *(
                                char_('*') >> factor_
                            |   char_('/') >> factor_
                            );

            factor_ = (attr('+') >> power_)
                        | (char_('-') >> power_)
                        | (char_('+') >> power_);

            // NOTE: '^' has right-to-left associativity here.
            power_ = base_
                        >> *(
                                char_('^') >> factor_
                            );

            base_ = uint_
                        | '(' >> expr_ >> ')';
        }

        qi::rule<Iterator, ast::expression(), qi::ascii::space_type> expr_;
        qi::rule<Iterator, ast::expression(), qi::ascii::space_type> term_;
        qi::rule<Iterator, ast::unary(), qi::ascii::space_type> factor_;
        qi::rule<Iterator, ast::expression(), qi::ascii::space_type> power_;
        qi::rule<Iterator, ast::operand(), qi::ascii::space_type> base_;
    };
} // namespace rocky::math::calc


#endif // ROCKY_MATH_CALC_CALCULATOR_H
