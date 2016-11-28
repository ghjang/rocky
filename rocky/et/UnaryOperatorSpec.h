#define n BOOST_PP_ITERATION()


//==============================================================================
#if UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))
    struct UNARY_OP_NAME(n)
    {
        template <typename T>
        static decltype(auto) apply(null_terminal, T && t)
        {
            return std::forward<T>(t) UNARY_OP_SYM(n);
        }
    };
#else
    struct UNARY_OP_NAME(n)
    {
        template <typename T>
        static decltype(auto) apply(T && t, null_terminal)
        {
            return UNARY_OP_SYM(n) std::forward<T>(t);
        }
    };
#endif // UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
auto op_sym_str(expression<Left, UNARY_OP_NAME(n), Right, IsLeftRValRef, IsRightRValRef>)
{
    return UNARY_OPERATOR_symbol_str(UNARY_OPERATOR_TUPLES_at(n));
}

template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
auto op_sym_desc(expression<Left, UNARY_OP_NAME(n), Right, IsLeftRValRef, IsRightRValRef>)
{
    return UNARY_OPERATOR_name_str(UNARYARY_OPERATOR_TUPLES_at(n))
           "("
           UNARY_OPERATOR_symbol_str(UNARYARY_OPERATOR_TUPLES_at(n))
           ")";
}


//==============================================================================
#if UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))
    template <typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
    auto operator UNARY_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, int)
    {
        using lhs_t = null_terminal;
        using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, false>{
                    null_terminal{}, e
            };
    }

    template <typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
    auto operator UNARY_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, int)
    {
        using lhs_t = null_terminal;
        using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, true>{
                    null_terminal{}, std::move(e)
            };
    }
#else
    template <typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
    auto operator UNARY_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e)
    {
        using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
        using rhs_t = null_terminal;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, false, true>{
                    e, null_terminal{}
            };
    }

    template <typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
    auto operator UNARY_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e)
    {
        using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
        using rhs_t = null_terminal;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, true>{
                    std::move(e), null_terminal{}
            };
    }
#endif // UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))


//==============================================================================
#if UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))
    template <typename T>
    auto operator UNARY_OP_SYM(n) (terminal<T> & t, int)
    {
        using lhs_t = null_terminal;
        using rhs_t = terminal<T>;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, false>{
                    null_terminal{}, t
            };
    }

    template <typename T>
    auto operator UNARY_OP_SYM(n) (terminal<T> && t, int)
    {
        using lhs_t = null_terminal;
        using rhs_t = terminal<T>;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, true>{
                    null_terminal{}, std::move(t)
            };
    }
#else
    template <typename T>
    auto operator UNARY_OP_SYM(n) (terminal<T> & t)
    {
        using lhs_t = terminal<T>;
        using rhs_t = null_terminal;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, false, true>{
                    t, null_terminal{}
            };
    }

    template <typename T>
    auto operator UNARY_OP_SYM(n) (terminal<T> && t)
    {
        using lhs_t = terminal<T>;
        using rhs_t = null_terminal;
        return expression<lhs_t, UNARY_OP_NAME(n), rhs_t, true, true>{
                    std::move(t), null_terminal{}
            };
    }
#endif // UNARY_OPERATOR_is_postfix(UNARY_OPERATOR_TUPLES_at(n))


//==============================================================================
#undef n
