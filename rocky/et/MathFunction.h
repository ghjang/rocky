#ifndef ROCKY_ET_MATH_FUNCTION_H
#define ROCKY_ET_MATH_FUNCTION_H


#include <cmath>
#include <type_traits>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include "rocky/et/ExpressionTemplate.h"


//==============================================================================
#define MATH_FUNCTION_SEQUENCE  \
            (sin)               \
            (cos)               \
            (tan)               


#define MATH_FUNC_NAME(i)   \
            BOOST_PP_SEQ_ELEM(i, MATH_FUNCTION_SEQUENCE)


//==============================================================================
#include <boost/preprocessor/iteration/iterate.hpp>
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(BOOST_PP_SEQ_SIZE(MATH_FUNCTION_SEQUENCE), 1))
#define BOOST_PP_FILENAME_1 "rocky/et/MathFunctionSpec.h"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_FILENAME_1
#undef BOOST_PP_ITERATION_LIMITS


//==============================================================================
template <template <typename> class MathFuncTerminal>
struct math_func_terminal_generator
{
    template <typename SubExpr>
    auto operator [] (SubExpr && expr) const
    { return MathFuncTerminal<std::decay_t<SubExpr>>{ std::forward<SubExpr>(expr) }; }
};


#define DEFINE_MATH_FUNC_KEYWORD_OBJ(r, data, func) \
            math_func_terminal_generator<BOOST_PP_CAT(func, _func_terminal_t)> const BOOST_PP_CAT(func, _){};


BOOST_PP_SEQ_FOR_EACH(DEFINE_MATH_FUNC_KEYWORD_OBJ, ~, MATH_FUNCTION_SEQUENCE)


#endif // ROCKY_ET_MATH_FUNCTION_H
