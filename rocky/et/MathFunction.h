#ifndef ROCKY_ET_MATH_FUNCTION_H
#define ROCKY_ET_MATH_FUNCTION_H


#include <cmath>
#include <type_traits>

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
    sin_func_terminal_t(SubExpr const& expr)
        : subExpr_{ expr }
    { }

    sin_func_terminal_t(SubExpr && expr)
        : subExpr_{ std::move(expr) }
    { }

    template <typename Context>
    auto operator () (Context & c)
    { return std::sin(subExpr_(c)); }

    SubExpr subExpr_;
};


template <template <typename> class MathFuncTerminal>
struct math_func_terminal_generator
{
    template <typename SubExpr>
    auto operator [] (SubExpr && expr) const
    { return MathFuncTerminal<std::decay_t<SubExpr>>{ std::forward<SubExpr>(expr) }; }
};


math_func_terminal_generator<sin_func_terminal_t> const sin_{};


#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(MATH_FUNCTION_SEQUENCE), 1))
#define BOOST_PP_FILENAME_1 "rocky/et/MathFunctionSpec.h"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_FILENAME_1
#undef BOOST_PP_ITERATION_LIMITS


#endif // ROCKY_ET_MATH_FUNCTION_H
