#ifndef ROCKY_ET_BINARY_OPERATOR_H
#define ROCKY_ET_BINARY_OPERATOR_H


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>


#define BINARY_OPERATOR_TUPLES          \
    (multiplication,    *)              \
    (division,          /)              \
    (remainder,         %)              \
    (addition,          +)              \
    (subtraction,       -)              \
    (left_shift,        <<)             \
    (right_shift,       >>)             \
    (sum,               +=)             \
    (difference,        -=)             \
    (product,           *=)             \
    (quotient,          /=)             \
    (remainder_assign,  %=)


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


#include "BinaryOperatorSpec.h"


#endif // ROCKY_ET_BINARY_OPERATOR_H
