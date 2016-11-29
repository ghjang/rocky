#ifndef ROCKY_ET_EXPRESSION_TRAITS_H
#define ROCKY_ET_EXPRESSION_TRAITS_H


#include "rocky/et/ExpressionTemplateFwd.h"


//==============================================================================
template <typename T>
struct is_callable_node : std::false_type
{ };

template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct is_callable_node<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        : std::true_type
{ };

template <typename T>
struct is_callable_node<terminal<T>>
        : std::true_type
{ };

template <std::size_t i>
struct is_callable_node<place_holder<i>>
        : std::true_type
{ };

template <bool IsValRValRef, typename T>
struct is_callable_node<value_holder<IsValRValRef, T>>
        : std::true_type
{ };

template <>
struct is_callable_node<null_terminal>
        : std::true_type
{ };


template <typename T>
struct is_expression : std::false_type
{ };

template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct is_expression<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>
        : std::true_type
{ };


template <typename T>
struct is_terminal : std::is_base_of<terminal<T>, T>
{ };

template <typename T>
struct is_terminal<terminal<T>> : std::true_type
{ };


#endif // ROCKY_ET_EXPRESSION_TRAITS_H
