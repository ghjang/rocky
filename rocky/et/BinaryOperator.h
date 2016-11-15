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


struct left_shift
{
    template <typename L, typename R>
    static decltype(auto) apply(L && l, R && r)
    {
        return std::forward<L>(l) << std::forward<R>(r);
    }
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto left_shift_expression_generator(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, left_shift, rhs_t, false, std::is_rvalue_reference<decltype(rhs)>::value>{
                lhs, std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto left_shift_expression_generator(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, left_shift, rhs_t, false, true>{
                lhs, rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto left_shift_expression_generator(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::true_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = std::decay_t<Rhs>;
    return expression<lhs_t, left_shift, rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value>{
                std::move(lhs), std::forward<Rhs>(rhs)
           };
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto left_shift_expression_generator(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs,
                                     Rhs && rhs,
                                     std::false_type)
{
    using lhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>;
    return expression<lhs_t, left_shift, rhs_t, true, true>{
                std::move(lhs), rhs_t{ std::forward<Rhs>(rhs) }
           };
}


template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto left_shift_expression_generator(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::true_type)
{
    using lhs_t = std::decay_t<Lhs>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, left_shift, rhs_t, std::is_rvalue_reference<decltype(lhs)>::value, false>{
                std::forward<Lhs>(lhs), rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto left_shift_expression_generator(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, left_shift, rhs_t, true, false>{
                lhs_t{ std::forward<Lhs>(lhs) }, rhs
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto left_shift_expression_generator(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs,
                                     std::true_type)
{
    using lhs_t = std::decay_t<Lhs>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, left_shift, rhs_t, std::is_rvalue_reference<decltype(lhs)>::value, true>{
                std::forward<Lhs>(lhs), std::move(rhs)
           };
}

template
<
    typename Lhs,
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
auto left_shift_expression_generator(Lhs && lhs,
                                     expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs,
                                     std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>;
    using rhs_t = expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>;
    return expression<lhs_t, left_shift, rhs_t, true, true>{
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(rhs)
           };
}


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename Rhs
>
auto operator << (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & lhs, Rhs && rhs)
{
    return left_shift_expression_generator(
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
auto operator << (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && lhs, Rhs && rhs)
{
    return left_shift_expression_generator(
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
auto operator << (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & rhs)
{
    return left_shift_expression_generator(
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
auto operator << (Lhs && lhs, expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && rhs)
{
    return left_shift_expression_generator(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}


template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(Lhs && lhs, terminal<Rhs> & rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, left_shift, Rhs, true, false> {
                lhs_t{ std::forward<Lhs>(lhs) }, *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(Lhs && lhs, terminal<Rhs> & rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, left_shift, Rhs, std::is_rvalue_reference<decltype(lhs)>::value, false> {
                std::forward<Lhs>(lhs), *(rhs.derived())
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(Lhs && lhs, terminal<Rhs> && rhs, std::false_type)
{
    using lhs_t = value_holder<std::is_rvalue_reference<decltype(lhs)>::value, std::decay_t<Lhs>>; 
    return expression<lhs_t, left_shift, Rhs, true, true> {
                lhs_t{ std::forward<Lhs>(lhs) }, std::move(*(rhs.derived()))
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(Lhs && lhs, terminal<Rhs> && rhs, std::true_type)
{
    using lhs_t = std::decay_t<Lhs>; 
    return expression<lhs_t, left_shift, Rhs, std::is_rvalue_reference<decltype(lhs)>::value, true> {
                std::forward<Lhs>(lhs), std::move(*(rhs.derived()))
           };
}


template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(terminal<Lhs> & lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, left_shift, rhs_t, false, true> {
                *(lhs.derived()), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(terminal<Lhs> & lhs, Rhs && rhs, std::true_type)
{
    using rhs_t = std::decay_t<Rhs>; 
    return expression<Lhs, left_shift, rhs_t, false, std::is_rvalue_reference<decltype(rhs)>::value> {
                *(lhs.derived()), std::forward<Rhs>(rhs)
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(terminal<Lhs> && lhs, Rhs && rhs, std::false_type)
{
    using rhs_t = value_holder<std::is_rvalue_reference<decltype(rhs)>::value, std::decay_t<Rhs>>; 
    return expression<Lhs, left_shift, rhs_t, true, true> {
                std::move(*(lhs.derived())), rhs_t{ std::forward<Rhs>(rhs) }
           };
}

template <typename Lhs, typename Rhs>
auto left_shift_terminal_generator(terminal<Lhs> && lhs, Rhs && rhs, std::true_type)
{
    using rhs_t = std::decay_t<Rhs>; 
    return expression<Lhs, left_shift, rhs_t, true, std::is_rvalue_reference<decltype(rhs)>::value> {
                std::move(*(lhs.derived())), std::forward<Rhs>(rhs)
           };
}


template <typename Lhs, typename Rhs>
auto operator << (Lhs && lhs, terminal<Rhs> & rhs)
{
    return left_shift_terminal_generator(
                std::forward<Lhs>(lhs),
                rhs,
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator << (Lhs && lhs, terminal<Rhs> && rhs)
{
    return left_shift_terminal_generator(
                std::forward<Lhs>(lhs),
                std::move(rhs),
                is_callable_node<std::decay_t<Lhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator << (terminal<Lhs> & lhs, Rhs && rhs)
{
    return left_shift_terminal_generator(
                lhs,
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}

template <typename Lhs, typename Rhs>
auto operator << (terminal<Lhs> && lhs, Rhs && rhs)
{
    return left_shift_terminal_generator(
                std::move(lhs),
                std::forward<Rhs>(rhs),
                is_callable_node<std::decay_t<Rhs>>()
           );
}
