#ifndef ROCKY_ET_PRINT_H
#define ROCKY_ET_PRINT_H


#include <ostream>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"


struct expression_tree_printer
{
    void print_prefix(int level)
    {
        for (int i = 0; i < level; ++i) {
            ostream_ << "  ";
        }
        if (level != 0) {
            ostream_ << "+- ";
        }
    }

    template
    <
        typename Expr,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void operator () (Expr && e, int level)
    {
        print_prefix(level);
        ostream_ << op_sym_str(std::forward<Expr>(e)) << '\n';
    }

    template <bool IsValRValRef, typename T>
    void operator () (value_holder<IsValRValRef, T> & v, int level)
    {
        print_prefix(level);
        ostream_ << v.get() << '\n';
    }

    template <std::size_t i>
    void operator () (place_holder<i>, int level)
    {
        print_prefix(level);
        ostream_ << '_' << i << '\n';
    }

    std::ostream & ostream_;
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_symbol(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, OStream & o)
{
    preorder(e, expression_tree_printer{ o });
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_symbol(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, OStream & o)
{
    preorder(std::move(e), expression_tree_printer{ o });
}


#endif // ROCKY_ET_PRINT_H
