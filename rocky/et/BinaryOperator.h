#ifndef ROCKY_ET_BINARY_OPERATOR_H
#define ROCKY_ET_BINARY_OPERATOR_H


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/size.hpp>


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


#include "BinaryOperatorSpec.h"


#endif // ROCKY_ET_BINARY_OPERATOR_H
