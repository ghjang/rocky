#ifndef ROCKY_ET_PRINT_H
#define ROCKY_ET_PRINT_H


#include <string>
#include <ostream>

#include <boost/type_index.hpp>

#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/Traversal.h"


//==============================================================================
struct expression_tree_printer
{
    void print_prefix(int level)
    {
        for (int i = 0; i < level; ++i) {
            for (int j = 0; j < indentSpaceCount_; ++j) {
                ostream_.put(' ');
            }
        }
        if (level != 0) {
            ostream_ << prefix_;
        }
    }

    template
    <
        typename Expr, typename TraversalContext,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void operator () (Expr && e, TraversalContext && c)
    {
        print_prefix(c.level_);
        ostream_ << op_sym_desc(std::forward<Expr>(e)) << '\n';
    }

    template <bool IsValRValRef, typename T, typename TraversalContext>
    void operator () (value_holder<IsValRValRef, T> & v, TraversalContext && c, std::true_type)
    {
        print_prefix(c.level_);
        ostream_ << boost::typeindex::type_id<std::decay_t<decltype(v.get())>>().pretty_name()
                 << '(' << v.get() << ")\n";
    }

    template <bool IsValRValRef, typename T, typename TraversalContext>
    void operator () (value_holder<IsValRValRef, T> & v, TraversalContext && c, std::false_type)
    {
        print_prefix(c.level_);
        ostream_ << boost::typeindex::type_id<std::decay_t<decltype(v.get())>>().pretty_name()
                 << '\n';
    }

    template <bool IsValRValRef, typename T, typename TraversalContext>
    void operator () (value_holder<IsValRValRef, T> & v, TraversalContext && c)
    {
        using value_t = std::decay_t<decltype(v.get())>;
        (*this)(
            v,
            std::forward<TraversalContext>(c),
            std::integral_constant<
                    bool,
                    !std::is_class<value_t>::value
                            || std::is_convertible<value_t, std::string>::value
            >{}
        );
    }

    template <typename TraversalContext>
    void operator () (value_holder<false, char const *> & v, TraversalContext && c)
    {
        print_prefix(c.level_);
        ostream_ << '"' << v.get() << "\"\n";
    }

    template <std::size_t i, typename TraversalContext>
    void operator () (place_holder<i>, TraversalContext && c)
    {
        print_prefix(c.level_);
        ostream_ << '_' << i << '\n';
    }

    std::ostream & ostream_;
    int indentSpaceCount_ = 2;
    std::string prefix_ = "+- ";
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, OStream & o)
{
    preorder(e, expression_tree_printer{ o, 2, "+- " });
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, OStream & o)
{
    preorder(std::move(e), expression_tree_printer{ o, 2, "+- " });
}


//==============================================================================
struct expression_string_printer
{
    template <typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
    void operator () (expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e)
    {
        ostream_ << '(';
        (*this)(e.left());
        ostream_ << ' ' << op_sym_str(e) << ' ';
        (*this)(e.right());
        ostream_ << ')';
    }

    template <bool IsValRValRef, typename T>
    void operator () (value_holder<IsValRValRef, T> & v)
    {
        ostream_ << v.get();
    }

    template <std::size_t i>
    void operator () (place_holder<i>)
    {
        ostream_ << '_' << i;
    }

    std::ostream & ostream_;
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree_to_str(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, OStream & o)
{
    expression_string_printer{ o }(e);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree_to_str(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, OStream & o)
{
    expression_string_printer{ o }(e);
}


//==============================================================================
struct expression_graphviz_dot_printer
{
    template 
    <
        typename Expr, typename Context,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void operator () (Expr && e, Context && c)
    {
    }

    template <bool IsValRValRef, typename T, typename Context>
    void operator () (value_holder<IsValRValRef, T> & v, Context && c)
    {
    }

    template <std::size_t i, typename Context>
    void operator () (place_holder<i>, Context && c)
    {
    }

    std::ostream & ostream_;
};


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree_to_graphviz_dot(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, OStream & o)
{
    o << "digraph Expression {\n";
    preorder(e, expression_graphviz_dot_printer{ o });
    o << "}\n";
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename OStream
>
void print_tree_to_graphviz_dot(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, OStream & o)
{
    o << "digraph Expression {\n";
    preorder(e, expression_graphviz_dot_printer{ o });
    o << "}\n";
}


#endif // ROCKY_ET_PRINT_H
