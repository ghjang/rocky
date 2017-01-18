#ifndef ROCKY_ET_BINARY_OPERATOR_H
#define ROCKY_ET_BINARY_OPERATOR_H


#include <cmath>

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

#include "rocky/base/MacroUtility.h"
#include "rocky/et/ExpressionTraits.h"


// NOTE:
//  - overloaded 'operator=' must be a non-static member function.
//  - overloaded 'operator->' must be a unary operator.

// NOTE: comma operator is treated specially inside the macro expansion.

#define BINARY_OPERATOR_TUPLES          \
    (addition,              +)          \
    (subtraction,           -)          \
    (multiplication,        *)          \
    (division,              /)          \
    (remainder,             %)          \
    (bitwise_and,           &)          \
    (bitwise_or,            |)          \
    (bitwise_xor,           ^)          \
    (left_shift,            <<)         \
    (right_shift,           >>)         \
    (sum_assign,            +=)         \
    (difference_assign,     -=)         \
    (product_assign,        *=)         \
    (quotient_assign,       /=)         \
    (remainder_assign,      %=)         \
    (bitwise_and_assign,    &=)         \
    (bitwise_or_assign,     |=)         \
    (bitwise_xor_assign,    ^=)         \
    (left_shift_assign,     <<=)        \
    (right_shift_assign,    >>=)        \
    (logical_and,           &&)         \
    (logical_or,            ||)         \
    (equal_to,              ==)         \
    (not_equal_to,          !=)         \
    (less_than,             <)          \
    (greater_than,          >)          \
    (less_or_equal,         <=)         \
    (greater_or_equal,      >=)         \
    (comma,                 BOOST_PP_COMMA())


#define BINARY_OPERATOR_TUPLES_to_tuple_seq(operators) \
    BOOST_PP_CAT(CREATE_PLACEHOLDER_FILLER_0 operators, _END)

#define BINARY_OPERATOR_TUPLES_size \
    BOOST_PP_SEQ_SIZE(BINARY_OPERATOR_TUPLES_to_tuple_seq(BINARY_OPERATOR_TUPLES))

#define BINARY_OPERATOR_TUPLES_at(i) \
    BOOST_PP_SEQ_ELEM(i, BINARY_OPERATOR_TUPLES_to_tuple_seq(BINARY_OPERATOR_TUPLES))

#define BINARY_OPERATOR_name(bin_op_tuple) \
    BOOST_PP_TUPLE_ELEM(0, bin_op_tuple)

#define BINARY_OPERATOR_name_str(bin_op_tuple) \
    TO_STR(BINARY_OPERATOR_name(bin_op_tuple))

#define BINARY_OPERATOR_symbol(bin_op_tuple) \
    BOOST_PP_TUPLE_ELEM(1, bin_op_tuple)

#define BINARY_OPERATOR_symbol_str(bin_op_tuple) \
    TO_STR(BINARY_OPERATOR_symbol(bin_op_tuple))


#define BIN_OP_NAME(i) \
    BOOST_PP_CAT(BINARY_OPERATOR_name(BINARY_OPERATOR_TUPLES_at(i)), _t)

#define BIN_OP_SYM(i)                                                           \
    BOOST_PP_IF(                                                                \
        BOOST_PP_EQUAL(                                                         \
            BOOST_PP_TUPLE_SIZE(BINARY_OPERATOR_TUPLES_at(i)),                  \
            3                                                                   \
        ),                                                                      \
        BOOST_PP_COMMA,                                                         \
        BOOST_PP_IDENTITY(BINARY_OPERATOR_symbol(BINARY_OPERATOR_TUPLES_at(i))) \
    )()


#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(BINARY_OPERATOR_TUPLES_size, 1))
#define BOOST_PP_FILENAME_1 "rocky/et/BinaryOperatorSpec.h"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_FILENAME_1
#undef BOOST_PP_ITERATION_LIMITS


// binary OpTag type for power
struct pow_t
{
    template <typename L, typename R>
    static auto apply(L && l, R && r)
    {
        return std::pow(std::forward<L>(l), std::forward<R>(r));
    }
};


#endif // ROCKY_ET_BINARY_OPERATOR_H
