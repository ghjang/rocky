#ifndef ROCKY_MATH_CALC_CALCULATOR_H
#define ROCKY_MATH_CALC_CALCULATOR_H


#include <cmath>
#include <functional>
#include <type_traits>
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
    using number_t = boost::variant<int, double>;

    enum instruction
    {
        op_neg,
        op_add,
        op_sub,
        op_mul,
        op_div,
        op_pow,
        op_int,
        op_double
    };

    using byte_code_t = boost::variant<number_t, instruction>;


    namespace detail
    {
        template <typename F, typename R = number_t>
        struct unary_op : boost::static_visitor<R>
        {
            unary_op(F f)
                : f_(f)
            { }

            template <typename Number>
            R operator () (Number n) const
            { return f_(n); }

            F f_;
        };

        template <typename UnaryOp>
        number_t exec_unary_op(number_t const& n, UnaryOp && op)
        {
            return boost::apply_visitor(
                            unary_op<std::decay_t<UnaryOp>>{ std::forward<UnaryOp>(op) },
                            n
                    );
        }


        template <typename F, typename R = number_t>
        struct binary_op : boost::static_visitor<R>
        {
            binary_op(F f)
                : f_(f)
            { }

            template <typename N1, typename N2>
            R operator () (N1 lhs, N2 rhs) const
            { return f_(lhs, rhs); }

            F f_;
        };

        template <typename BinaryOp>
        number_t exec_binary_op(number_t const& lhs, number_t const& rhs, BinaryOp && op)
        {
            return boost::apply_visitor(
                            binary_op<std::decay_t<BinaryOp>>{ std::forward<BinaryOp>(op) },
                            lhs, rhs
                    );
        }


        struct number_to_int
        {
            constexpr int operator () (int n) const
            { return n; }

            constexpr int operator () (double n) const
            { return static_cast<int>(n); }
        };

        int to_int(number_t const& n)
        {
            return boost::apply_visitor(
                            unary_op<number_to_int, int>{ number_to_int{} },
                            n
                    );
        }
    } // namespace detail


    class vmachine
    {
    public:
        vmachine(unsigned stackSize = 4096)
          : stack_(stackSize)
          , stackPtr_(stack_.begin())
        {  }

        number_t top() const { return stackPtr_[-1]; };
        int top_as_int() const { return detail::to_int(top()); };

        void execute(std::vector<byte_code_t> const& code);

    private:
        template <typename F>
        void execute_unary_op(F && f);

        template <typename F>
        void execute_binary_op(F && f);

    private:
        std::vector<number_t> stack_;
        std::vector<number_t>::iterator stackPtr_;
    };

    void vmachine::execute(std::vector<byte_code_t> const& code)
    {
        auto pc = code.begin();
        stackPtr_ = stack_.begin();

        auto const power = [](auto lhs, auto rhs) { return std::pow(lhs, rhs); };

        while (pc != code.end())
        {
            switch (boost::get<instruction>(*pc++))
            {
                case op_neg: execute_unary_op(std::negate<>{}); break;

                case op_add: execute_binary_op(std::plus<>{});          break;
                case op_sub: execute_binary_op(std::minus<>{});         break;
                case op_mul: execute_binary_op(std::multiplies<>{});    break;
                case op_div: execute_binary_op(std::divides<>{});       break;
                case op_pow: execute_binary_op(power);                  break;

                case op_int:
                case op_double:
                    *stackPtr_++ = boost::get<number_t>(*pc++);
                    break;
            }
        }
    }

    template <typename F>
    void vmachine::execute_unary_op(F && f)
    {
        stackPtr_[-1] = detail::exec_unary_op(
                                    stackPtr_[-1],
                                    std::forward<F>(f)
                        );
    }

    template <typename F>
    void vmachine::execute_binary_op(F && f)
    {
        --stackPtr_;
        stackPtr_[-1] = detail::exec_binary_op(
                                    stackPtr_[-1], stackPtr_[0],
                                    std::forward<F>(f)
                        );
    }


    struct compiler : boost::static_visitor<>
    {
        std::vector<byte_code_t> & code_;

        compiler(std::vector<byte_code_t> & code)
          : code_(code)
        { }

        void operator()(ast::nil) const
        { BOOST_ASSERT(0); }

        void operator()(unsigned int n) const
        {
            code_.push_back(op_int);

            // TODO: check this unsigned int to int conversion is safe.
            code_.push_back(number_t{ static_cast<int>(n) });
        }

        void operator()(double n) const
        {
            code_.push_back(op_double);
            code_.push_back(number_t{ n });
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
        calculator() : calculator::base_type(additive_expr_)
        {
            using qi::char_;
            using qi::uint_;
            using qi::attr;

            additive_expr_ = multiplicative_expr
                                >> *(
                                        char_('+') >> multiplicative_expr
                                    |   char_('-') >> multiplicative_expr
                                    );

            multiplicative_expr = unary_expr_
                                    >> *(
                                            char_('*') >> unary_expr_
                                        |   char_('/') >> unary_expr_
                                        );

            unary_expr_ = (attr('+') >> primary_expr_)
                            | (char_('-') >> primary_expr_)
                            | (char_('+') >> primary_expr_);

            // NOTE: '^' has right-to-left associativity here.
            primary_expr_ = base_expr_
                                >> *(
                                        char_('^') >> unary_expr_
                                    );

            base_expr_ = uint_
                            | '(' >> additive_expr_ >> ')';
        }

        using expression_t = qi::rule<Iterator, ast::expression(), qi::ascii::space_type>;
        using unary_t = qi::rule<Iterator, ast::unary(), qi::ascii::space_type>;
        using operand_t = qi::rule<Iterator, ast::operand(), qi::ascii::space_type>;

        expression_t    additive_expr_;
        expression_t    multiplicative_expr;
        unary_t         unary_expr_;
        expression_t    primary_expr_;
        operand_t       base_expr_;
    };
} // namespace rocky::math::calc


#endif // ROCKY_MATH_CALC_CALCULATOR_H
