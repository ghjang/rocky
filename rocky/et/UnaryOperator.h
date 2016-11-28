#ifndef ROCKY_ET_UNARY_OPERATOR_H
#define ROCKY_ET_UNARY_OPERATOR_H


#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>


#include "rocky/base/MacroUtility.h"


// NOTE: (address_of, &) operator is not added intentionally.
//       It causes some compile error at the moment.

#define UNARY_OPERATOR_TUPLES           \
    (prefix_increment,  ++)             \
    (prefix_decrement,  --)             \
    (postfix_increment, ++, int)        \
    (postfix_decrement, --, int)        \
    (unary_plus,        +)              \
    (unary_minus,       -)              \
    (logical_not,       !)              \
    (bitwise_not,       ~)              \
    (indirection,       *)


#define UNARY_OPERATOR_TUPLES_to_tuple_seq(operators) \
    BOOST_PP_CAT(CREATE_PLACEHOLDER_FILLER_0 operators, _END)

#define UNARY_OPERATOR_TUPLES_size \
    BOOST_PP_SEQ_SIZE(UNARY_OPERATOR_TUPLES_to_tuple_seq(UNARY_OPERATOR_TUPLES))

#define UNARY_OPERATOR_TUPLES_at(i) \
    BOOST_PP_SEQ_ELEM(i, UNARY_OPERATOR_TUPLES_to_tuple_seq(UNARY_OPERATOR_TUPLES))

#define UNARY_OPERATOR_name(unary_op_tuple) \
    BOOST_PP_TUPLE_ELEM(0, unary_op_tuple)

#define UNARY_OPERATOR_name_str(unary_op_tuple) \
    TO_STR(UNARY_OPERATOR_name(unary_op_tuple))

#define UNARY_OPERATOR_symbol(unary_op_tuple) \
    BOOST_PP_TUPLE_ELEM(1, unary_op_tuple)

#define UNARY_OPERATOR_symbol_str(unary_op_tuple) \
    TO_STR(UNARY_OPERATOR_symbol(unary_op_tuple))

#define UNARY_OPERATOR_is_postfix(unary_op_tuple) \
    BOOST_PP_EQUAL(BOOST_PP_TUPLE_SIZE(unary_op_tuple), 3)


#define UNARY_OP_NAME(i)                                                            \
    BOOST_PP_IF(                                                                    \
        UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(i)),                     \
        BOOST_PP_CAT(UNARY_OPERATOR_name(UNARY_OPERATOR_TUPLES_at(i)), _postfix_t), \
        BOOST_PP_CAT(UNARY_OPERATOR_name(UNARY_OPERATOR_TUPLES_at(i)), _prefix_t)   \
    )

#define UNARY_OP_SYM(i) \
    UNARY_OPERATOR_symbol(UNARY_OPERATOR_TUPLES_at(i))


#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(UNARY_OPERATOR_TUPLES_size, 1))
#define BOOST_PP_FILENAME_1 "rocky/et/UnaryOperatorSpec.h"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_FILENAME_1
#undef BOOST_PP_ITERATION_LIMITS


#endif // ROCKY_ET_UNARY_OPERATOR_H
