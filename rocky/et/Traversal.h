#ifndef ROCKY_ET_TRAVERSAL_H
#define ROCKY_ET_TRAVERSAL_H


#include <type_traits>
#include <functional>


//==============================================================================
template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct expression;

template <typename Derived>
struct terminal;

template <typename T>
struct is_terminal;


//==============================================================================
enum struct NodePositionType
{
    Root,
    LeftChild,
    RightChild
};

template <typename PrevNode>
struct traversal_context
{
    int level_ = 0;
    std::reference_wrapper<int> seqNo_;
    NodePositionType nodePosition_ = NodePositionType::Root;
    PrevNode & prevNode_;
};

template <typename Context, typename Expr>
auto make_next_traversal_context(Context & c, NodePositionType t, Expr & e)
{
    return traversal_context<Expr>{
                c.level_ + 1,
                ++(c.seqNo_),
                t,
                e
           };
}


//==============================================================================
template
<
    typename Expr, typename F, typename Context,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto preorder_impl(Expr && e, F && f, Context && c)
{
    f(std::forward<Expr>(e), c);
    preorder_impl(
        e.left(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::LeftChild, e)
    );
    preorder_impl(
        e.right(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::RightChild, e)
    );
}

template <typename T, typename F, typename Context>
auto preorder_impl(terminal<T> & t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F, typename Context>
auto preorder_impl(terminal<T> && t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
{
    int seqNo = 0;
    preorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
{
    int seqNo = 0;
    preorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}


//==============================================================================
template
<
    typename Expr, typename F, typename Context,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto inorder_impl(Expr && e, F && f, Context && c)
{
    inorder_impl(
        e.left(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::LeftChild, e)
    );
    f(std::forward<Expr>(e), c);
    inorder_impl(
        e.right(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::RightChild, e)
    );
}

template <typename T, typename F, typename Context>
auto inorder_impl(terminal<T> & t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F, typename Context>
auto inorder_impl(terminal<T> && t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
{
    int seqNo = 0;
    inorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
{
    int seqNo = 0;
    inorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}


//==============================================================================
template
<
    typename Expr, typename F, typename Context,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto postorder_impl(Expr && e, F && f, Context && c)
{
    postorder_impl(
        e.left(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::LeftChild, e)
    );
    postorder_impl(
        e.right(),
        std::forward<F>(f),
        make_next_traversal_context(c, NodePositionType::RightChild, e)
    );
    f(std::forward<Expr>(e), c);
}

template <typename T, typename F, typename Context>
auto postorder_impl(terminal<T> & t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F, typename Context>
auto postorder_impl(terminal<T> && t, F && f, Context && c)
{
    f(*(t.derived()), c);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto postorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
{
    int seqNo = 0;
    postorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto postorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
{
    int seqNo = 0;
    postorder_impl(
        e,
        std::forward<F>(f),
        traversal_context<std::remove_reference_t<decltype(e)>>{ // root context
            0,
            std::ref(seqNo),
            NodePositionType::Root,
            e
        }
    );
}


#endif // ROCKY_ET_TRAVERSAL_H
