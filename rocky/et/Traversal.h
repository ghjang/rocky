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

struct traversal_context
{
    int level_ = 0;
    std::reference_wrapper<int> seqNo_;
    NodePositionType nodePosition_ = NodePositionType::Root;
};


//==============================================================================
template
<
    typename Expr, typename F,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto preorder_impl(Expr && e, F && f, traversal_context && c)
{
    f(std::forward<Expr>(e), c);
    preorder_impl(
        e.left(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::LeftChild }
    );
    preorder_impl(
        e.right(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::RightChild }
    );
}

template <typename T, typename F>
auto preorder_impl(terminal<T> & t, F && f, traversal_context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F>
auto preorder_impl(terminal<T> && t, F && f, traversal_context && c)
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
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
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
        std::move(e),
        std::forward<F>(f),
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
    );
}


//==============================================================================
template
<
    typename Expr, typename F,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto inorder_impl(Expr && e, F && f, traversal_context && c)
{
    inorder_impl(
        e.left(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::LeftChild }
    );
    f(std::forward<Expr>(e), c);
    inorder_impl(
        e.right(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::RightChild }
    );
}

template <typename T, typename F>
auto inorder_impl(terminal<T> & t, F && f, traversal_context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F>
auto inorder_impl(terminal<T> && t, F && f, traversal_context && c)
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
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
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
        std::move(e),
        std::forward<F>(f),
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
    );
}


//==============================================================================
template
<
    typename Expr, typename F,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto postorder_impl(Expr && e, F && f, traversal_context && c)
{
    postorder_impl(
        e.left(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::LeftChild }
    );
    postorder_impl(
        e.right(),
        std::forward<F>(f),
        traversal_context{ c.level_ + 1, ++(c.seqNo_), NodePositionType::RightChild }
    );
    f(std::forward<Expr>(e), c);
}

template <typename T, typename F>
auto postorder_impl(terminal<T> & t, F && f, traversal_context && c)
{
    f(*(t.derived()), c);
}

template <typename T, typename F>
auto postorder_impl(terminal<T> && t, F && f, traversal_context && c)
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
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
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
        std::move(e),
        std::forward<F>(f),
        traversal_context{ 0, std::ref(seqNo), NodePositionType::Root }
    );
}


#endif // ROCKY_ET_TRAVERSAL_H
