#ifndef ROCKAY_ET_EXPRESSION_TEMPLATE_FWD_H
#define ROCKAY_ET_EXPRESSION_TEMPLATE_FWD_H


template <typename Derived>
struct terminal;

template <std::size_t i>
struct place_holder;

template <bool IsValRValRef, typename T>
struct value_holder;

struct null_terminal;

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    template <typename, typename, bool, bool> class Storage
>
struct expression;


#endif // ROCKAY_ET_EXPRESSION_TEMPLATE_FWD_H
