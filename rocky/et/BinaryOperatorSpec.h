#define n BOOST_PP_ITERATION()


//==============================================================================
struct BIN_OP_NAME(n)
{
    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return std::forward<L>(l) BIN_OP_SYM(n) std::forward<R>(r);
    }
};


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
auto op_sym_str(expression<Left, BIN_OP_NAME(n), Right, IsLeftRValRef, IsRightRValRef>)
{
    return BINARY_OPERATOR_symbol_str(BINARY_OPERATOR_TUPLES_at(n));
}

template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
auto op_sym_desc(expression<Left, BIN_OP_NAME(n), Right, IsLeftRValRef, IsRightRValRef>)
{
    return BINARY_OPERATOR_name_str(BINARY_OPERATOR_TUPLES_at(n))
           "("
           BINARY_OPERATOR_symbol_str(BINARY_OPERATOR_TUPLES_at(n))
           ")";
}


//==============================================================================
template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, false, std::is_rvalue_reference<decltype(rhs)>::value>{
                lhs, std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, false, true>{
                lhs, rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value>{
                std::move(lhs), std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, true, true>{
                std::move(lhs), rhs_t{ std::forward<Rhs>(rhs) }
           };
}


template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::true_type)
{
    using lhs_t = std::decay_t<Lhs>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, std::is_rvalue_reference<decltype(lhs)>::value, false>{
                std::forward<Lhs>(lhs), rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, true, false>{
                lhs_t{ std::forward<Lhs>(lhs) }, rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                                     Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME(n), rhs_t, true, true>{
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(rhs)
           };
}


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs,
    typename = std::enable_if_t<!is_expression<std::decay_t<Rhs>>::value>
>
auto operator BIN_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                lhs,
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs,
    typename = std::enable_if_t<!is_expression<std::decay_t<Rhs>>::value>
>
auto operator BIN_OP_SYM(n) (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                std::move(lhs),
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename = std::enable_if_t<!is_expression<std::decay_t<Lhs>>::value>
>
auto operator BIN_OP_SYM(n) (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                std::forward<Lhs>(lhs),
                rhs,
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename = std::enable_if_t<!is_expression<std::decay_t<Lhs>>::value>
>
auto operator BIN_OP_SYM(n) (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template
<
    typename Left1, typename OpTag1, typename Right1, bool IsLeftRValRef1, bool IsRightRValRef1,
    typename Left2, typename OpTag2, typename Right2, bool IsLeftRValRef2, bool IsRightRValRef2
>
auto operator BIN_OP_SYM(n) (expression<Left1, OpTag1, Right1, IsLeftRValRef1, IsRightRValRef1> & lhs,
                             expression<Left2, OpTag2, Right2, IsLeftRValRef2, IsRightRValRef2> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                lhs,
                rhs,
                std::true_type{}
           );
}

template
<
    typename Left1, typename OpTag1, typename Right1, bool IsLeftRValRef1, bool IsRightRValRef1,
    typename Left2, typename OpTag2, typename Right2, bool IsLeftRValRef2, bool IsRightRValRef2
>
auto operator BIN_OP_SYM(n) (expression<Left1, OpTag1, Right1, IsLeftRValRef1, IsRightRValRef1> & lhs,
                             expression<Left2, OpTag2, Right2, IsLeftRValRef2, IsRightRValRef2> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                lhs,
                std::move(rhs),
                std::true_type{}
           );
}

template
<
    typename Left1, typename OpTag1, typename Right1, bool IsLeftRValRef1, bool IsRightRValRef1,
    typename Left2, typename OpTag2, typename Right2, bool IsLeftRValRef2, bool IsRightRValRef2
>
auto operator BIN_OP_SYM(n) (expression<Left1, OpTag1, Right1, IsLeftRValRef1, IsRightRValRef1> && lhs,
                             expression<Left2, OpTag2, Right2, IsLeftRValRef2, IsRightRValRef2> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                std::move(lhs),
                rhs,
                std::true_type{}
           );
}

template
<
    typename Left1, typename OpTag1, typename Right1, bool IsLeftRValRef1, bool IsRightRValRef1,
    typename Left2, typename OpTag2, typename Right2, bool IsLeftRValRef2, bool IsRightRValRef2
>
auto operator BIN_OP_SYM(n) (expression<Left1, OpTag1, Right1, IsLeftRValRef1, IsRightRValRef1> && lhs,
                             expression<Left2, OpTag2, Right2, IsLeftRValRef2, IsRightRValRef2> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _expression_generator)(
                std::move(lhs),
                std::move(rhs),
                std::true_type{}
           );
}


//==============================================================================
template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(Lhs && lhs, terminal<Rhs> & rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, BIN_OP_NAME(n), Rhs, true, false> {
                lhs_t{ std::forward<Lhs>(lhs) }, *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(Lhs && lhs, terminal<Rhs> & rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, BIN_OP_NAME(n), Rhs, std::is_rvalue_reference<decltype(lhs)>::value, false> {
                std::forward<Lhs>(lhs), *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(Lhs && lhs, terminal<Rhs> && rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, BIN_OP_NAME(n), Rhs, true, true> {
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(*(rhs.derived()))
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(Lhs && lhs, terminal<Rhs> && rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, BIN_OP_NAME(n), Rhs, std::is_rvalue_reference<decltype(lhs)>::value, true> {
                std::forward<Lhs>(lhs), std::move(*(rhs.derived()))
           };
}


template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(terminal<Lhs> & lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, BIN_OP_NAME(n), rhs_t, false, true> {
                *(lhs.derived()), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(terminal<Lhs> && lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, BIN_OP_NAME(n), rhs_t, true, true> {
                std::move(*(lhs.derived())), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(terminal<Lhs> && lhs, Rhs && rhs, std::true_type)
{
    using rhs_t = std::decay_t<Rhs>; 
    return expression<Lhs, BIN_OP_NAME(n), rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value> {
                std::move(*(lhs.derived())), std::forward<Rhs>(rhs)
           };
}


template 
<
    typename Lhs, typename Rhs,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Lhs>>::value>
>
auto operator BIN_OP_SYM(n) (Lhs && lhs, terminal<Rhs> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                std::forward<Lhs>(lhs),
                rhs,
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template 
<
    typename Lhs, typename Rhs,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Lhs>>::value>
>
auto operator BIN_OP_SYM(n) (Lhs && lhs, terminal<Rhs> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template 
<
    typename Lhs, typename Rhs,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Rhs>>::value>
>
auto operator BIN_OP_SYM(n) (terminal<Lhs> & lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                lhs,
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template 
<
    typename Lhs, typename Rhs,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Rhs>>::value>
>
auto operator BIN_OP_SYM(n) (terminal<Lhs> && lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                std::move(lhs),
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}


template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM(n) (terminal<Lhs> & lhs, terminal<Rhs> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                lhs,
                rhs,
                std::true_type{}
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM(n) (terminal<Lhs> & lhs, terminal<Rhs> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                lhs,
                std::move(rhs),
                std::true_type{}
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM(n) (terminal<Lhs> && lhs, terminal<Rhs> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                std::move(lhs),
                rhs,
                std::true_type{}
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM(n) (terminal<Lhs> && lhs, terminal<Rhs> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME(n), _terminal_generator)(
                std::move(lhs),
                std::move(rhs),
                std::true_type{}
           );
}


//==============================================================================
#undef n
