#ifndef ROCKY_ET_MATH_FUNCTION_H
#define ROCKY_ET_MATH_FUNCTION_H


#include <cmath>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/seq/size.hpp>

#include "rocky/et/ExpressionTemplate.h"


#define MATH_FUNCTION_SEQUENCE  \
            (sin)               \
            (cos)               \
            (tan)               


template <typename SubExpr>
struct sin_func_terminal_t
        : terminal<sin_func_terminal_t<SubExpr>>
{
    template <typename Context>
    decltype(auto) operator () (Context & c)
    { return std::sin(subExpr_(c)); }

    SubExpr subExpr_;
};


struct sin_func_terminal_generator
{
    template <typename SubExpr>
    decltype(auto) operator [] (SubExpr expr)
    { return sin_func_terminal_t<SubExpr>{ expr }; }
};


sin_func_terminal_generator const sin_{};


#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(MATH_FUNCTION_SEQUENCE), 1))
#define BOOST_PP_FILENAME_1 "rocky/et/MathFunctionSpec.h"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_FILENAME_1
#undef BOOST_PP_ITERATION_LIMITS


#endif // ROCKY_ET_MATH_FUNCTION_H
