#ifndef ROCKY_ET_TRAVERSAL_H
#define ROCKY_ET_TRAVERSAL_H


#include <type_traits>
#include <functional>

#include "rocky/et/ExpressionTemplateFwd.h"


//==============================================================================
enum struct NodePositionType
{
    Null,
    Root,
    LeftChild,
    RightChild
};


struct empty_traversal_context
{
    template <typename Number>
    static auto make_null_context(Number & /* seqNo */)
    {
        return empty_traversal_context{};
    }

    template <typename Context, typename Expr>
    static auto make_next_context(Context & /* c */,
                                  NodePositionType /* t */,
                                  Expr & /* e */)
    {
        return empty_traversal_context{};
    }
};


struct traversal_context_with_level_info
{
    struct context
    {
        int level_ = -1;
    };

    template <typename Number>
    static auto make_null_context(Number & /* seqNo */)
    {
        return traversal_context_with_level_info::context{};
    }

    template <typename Context, typename Expr>
    static auto make_next_context(Context & c,
                                  NodePositionType /* t */,
                                  Expr & /* e */)
    {
        return traversal_context_with_level_info::context{
                    c.level_ + 1
               };
    }
};


struct traversal_context_with_parent_info
{
    template <typename ParentNode, typename ParentContext>
    struct context
    {
        int level_ = -1;
        int id_ = -1;
        std::reference_wrapper<int> seqNo_;
        NodePositionType nodePosition_ = NodePositionType::Null;
        ParentNode * parentNode_ = nullptr;
        ParentContext * parentContext_ = nullptr;
    };

    using null_parent_info_context_t
            = traversal_context_with_parent_info::context<void, void>;

    template <typename Number>
    static auto make_null_context(Number & seqNo)
    {
        return null_parent_info_context_t{
                    -1, // null level
                    -1, // null id
                    std::ref(seqNo),
                    NodePositionType::Null,
                    nullptr,
                    nullptr
               };
    }

    template <typename Context, typename Expr>
    static auto make_next_context(Context & c, NodePositionType t, Expr & e)
    {
        return traversal_context_with_parent_info::context<Expr, Context>{
                    c.level_ + 1,
                    c.seqNo_ + 1,
                    ++(c.seqNo_),
                    t,
                    &e,
                    &c
               };
    }
};


//==============================================================================
template <typename Derived>
struct pre_order
{
private:
    template <typename F, typename Node, typename Context>
    void call_impl(Node && node, F && f, Context && c)
    {
        f(node, c);
    }

    template <typename F, typename Node>
    void call_impl(Node && node, F && f, empty_traversal_context &&)
    {
        f(node);
    }

    template
    <
        typename Expr, typename F, typename Context,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void preorder_impl(Expr && e, F && f, Context && c)
    {
        call_impl(
            std::forward<Expr>(e),
            std::forward<F>(f),
            std::forward<Context>(c)
        );
        preorder_impl(
            e.left(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::LeftChild, e)
        );
        preorder_impl(
            e.right(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::RightChild, e)
        );
    }

    template <typename T, typename F, typename Context>
    void preorder_impl(terminal<T> & t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

    template <typename T, typename F, typename Context>
    void preorder_impl(terminal<T> && t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

public:
    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        preorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }

    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        preorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }
};


//==============================================================================
template <typename Derived>
struct in_order
{
private:
    template <typename F, typename Node, typename Context>
    void call_impl(Node && node, F && f, Context && c)
    {
        f(node, c);
    }

    template <typename F, typename Node>
    void call_impl(Node && node, F && f, empty_traversal_context &&)
    {
        f(node);
    }

    template
    <
        typename Expr, typename F, typename Context,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void inorder_impl(Expr && e, F && f, Context && c)
    {
        inorder_impl(
            e.left(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::LeftChild, e)
        );
        call_impl(
            std::forward<Expr>(e),
            std::forward<F>(f),
            std::forward<Context>(c)
        );
        inorder_impl(
            e.right(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::RightChild, e)
        );
    }

    template <typename T, typename F, typename Context>
    void inorder_impl(terminal<T> & t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

    template <typename T, typename F, typename Context>
    void inorder_impl(terminal<T> && t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

public:
    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        inorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }

    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        inorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }
};


//==============================================================================
template <typename Derived>
struct post_order
{
private:
    template <typename F, typename Node, typename Context>
    void call_impl(Node && node, F && f, Context && c)
    {
        f(node, c);
    }

    template <typename F, typename Node>
    void call_impl(Node && node, F && f, empty_traversal_context &&)
    {
        f(node);
    }

    template
    <
        typename Expr, typename F, typename Context,
        typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
    >
    void postorder_impl(Expr && e, F && f, Context && c)
    {
        postorder_impl(
            e.left(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::LeftChild, e)
        );
        postorder_impl(
            e.right(),
            std::forward<F>(f),
            Derived::make_next_context(c, NodePositionType::RightChild, e)
        );
        call_impl(
            std::forward<Expr>(e),
            std::forward<F>(f),
            std::forward<Context>(c)
        );
    }

    template <typename T, typename F, typename Context>
    void postorder_impl(terminal<T> & t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

    template <typename T, typename F, typename Context>
    void postorder_impl(terminal<T> && t, F && f, Context && c)
    {
        call_impl(*(t.derived()), std::forward<F>(f), std::forward<Context>(c));
    }

public:
    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        postorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }

    template
    <
        typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
        typename F
    >
    void go(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
    {
        int seqNo = -1; // for null context
        auto nullContext = Derived::make_null_context(seqNo);
        postorder_impl(
            e,
            std::forward<F>(f),
            Derived::make_next_context(nullContext, NodePositionType::Root, e)
        );
    }
};


template 
<
    template <typename> class Order,
    typename TraversalContext = empty_traversal_context
>
struct expression_traversal
        : Order<expression_traversal<Order, TraversalContext>>
        , TraversalContext
{ };


#endif // ROCKY_ET_TRAVERSAL_H
