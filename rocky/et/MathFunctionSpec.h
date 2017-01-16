#define n BOOST_PP_ITERATION()

//==============================================================================
template <typename SubExpr>
struct BOOST_PP_CAT(MATH_FUNC_NAME(n), _func_terminal_t)
        : terminal<BOOST_PP_CAT(MATH_FUNC_NAME(n), _func_terminal_t<SubExpr>)>
{
    BOOST_PP_CAT(MATH_FUNC_NAME(n), _func_terminal_t)(SubExpr const& expr)
        : subExpr_{ expr }
    { }

    BOOST_PP_CAT(MATH_FUNC_NAME(n), _func_terminal_t)(SubExpr && expr)
        : subExpr_{ std::move(expr) }
    { }

    template
    <
        typename T,
        typename = std::enable_if_t<std::is_arithmetic<T>::value>
    >
    auto operator () (T t)
    {
        auto arg{ std::make_tuple(t) };
        functor_context<decltype(arg)> c{ arg };
        return (*this)(c);
    }

    template 
    <
        typename Context,
        typename = std::enable_if_t<std::is_class<Context>::value>
    >
    auto operator () (Context & c)
    { return std::MATH_FUNC_NAME(n)(subExpr_(c)); }

    SubExpr subExpr_;
};


//==============================================================================
#undef n
