#define n BOOST_PP_ITERATION()


#define BIN_OP_NAME BOOST_PP_CAT(BINARY_OPERATOR_name(BINARY_OPERATOR_TUPLES_at(n)), _t)
#define BIN_OP_SYM BINARY_OPERATOR_symbol(BINARY_OPERATOR_TUPLES_at(n))


struct BIN_OP_NAME
{
    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return std::forward<L>(l) BIN_OP_SYM std::forward<R>(r);
    }
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, false, std::is_rvalue_reference<decltype(rhs)>::value>{
                lhs, std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, false, true>{
                lhs, rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value>{
                std::move(lhs), std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, true, true>{
                std::move(lhs), rhs_t{ std::forward<Rhs>(rhs) }
           };
}


template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::true_type)
{
    using lhs_t = std::decay_t<Lhs>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, std::is_rvalue_reference<decltype(lhs)>::value, false>{
                std::forward<Lhs>(lhs), rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, true, false>{
                lhs_t{ std::forward<Lhs>(lhs) }, rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs,
                                     std::true_type)
{
    using lhs_t = std::decay_t<Lhs>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, std::is_rvalue_reference<decltype(lhs)>::value, true>{
                std::forward<Lhs>(lhs), std::move(rhs)
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, BIN_OP_NAME, rhs_t, true, true>{
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(rhs)
           };
}


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto operator BIN_OP_SYM (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(
                lhs,
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto operator BIN_OP_SYM (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(
                std::move(lhs),
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto operator BIN_OP_SYM (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(
                std::forward<Lhs>(lhs),
                rhs,
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto operator BIN_OP_SYM (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _expression_generator)(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}


template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(Lhs && lhs, terminal<Rhs> & rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, BIN_OP_NAME, Rhs, true, false> {
                lhs_t{ std::forward<Lhs>(lhs) }, *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(Lhs && lhs, terminal<Rhs> & rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, BIN_OP_NAME, Rhs, std::is_rvalue_reference<decltype(lhs)>::value, false> {
                std::forward<Lhs>(lhs), *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(Lhs && lhs, terminal<Rhs> && rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, BIN_OP_NAME, Rhs, true, true> {
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(*(rhs.derived()))
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(Lhs && lhs, terminal<Rhs> && rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, BIN_OP_NAME, Rhs, std::is_rvalue_reference<decltype(lhs)>::value, true> {
                std::forward<Lhs>(lhs), std::move(*(rhs.derived()))
           };
}


template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(terminal<Lhs> & lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, BIN_OP_NAME, rhs_t, false, true> {
                *(lhs.derived()), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(terminal<Lhs> & lhs, Rhs && rhs, std::true_type)
{
    using rhs_t = std::decay_t<Rhs>; 
    return expression<Lhs, BIN_OP_NAME, rhs_t, false, std::is_rvalue_reference<decltype(rhs)>::value> {
                *(lhs.derived()), std::forward<Rhs>(rhs)
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(terminal<Lhs> && lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, BIN_OP_NAME, rhs_t, true, true> {
                std::move(*(lhs.derived())), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(terminal<Lhs> && lhs, Rhs && rhs, std::true_type)
{
    using rhs_t = std::decay_t<Rhs>; 
    return expression<Lhs, BIN_OP_NAME, rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value> {
                std::move(*(lhs.derived())), std::forward<Rhs>(rhs)
           };
}


template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM (Lhs && lhs, terminal<Rhs> & rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(
                std::forward<Lhs>(lhs),
                rhs,
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM (Lhs && lhs, terminal<Rhs> && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM (terminal<Lhs> & lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(
                lhs,
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator BIN_OP_SYM (terminal<Lhs> && lhs, Rhs && rhs)
{
    return BOOST_PP_CAT(BIN_OP_NAME, _terminal_generator)(
                std::move(lhs),
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}


#undef BIN_OP_NAME
#undef BIN_OP_SYM
#undef n
