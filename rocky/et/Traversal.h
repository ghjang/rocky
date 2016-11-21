#ifndef ROCKY_ET_TRAVERSAL_H
#define ROCKY_ET_TRAVERSAL_H


#include <type_traits>


//==============================================================================
template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct expression;

template <typename Derived>
struct terminal;

template <typename T>
struct is_terminal;


//==============================================================================
template
<
    typename Expr, typename F,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto preorder_impl(Expr && e, F && f, int level)
{
    f(std::forward<Expr>(e), level);
    preorder_impl(e.left(), std::forward<F>(f), level + 1);
    preorder_impl(e.right(), std::forward<F>(f), level + 1);
}

template <typename T, typename F>
auto preorder_impl(terminal<T> & t, F && f, int level)
{
    f(*(t.derived()), level);
}

template <typename T, typename F>
auto preorder_impl(terminal<T> && t, F && f, int level)
{
    f(*(t.derived()), level);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
{
    preorder_impl(e, std::forward<F>(f), 0);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
{
    preorder_impl(std::move(e), std::forward<F>(f), 0);
}


//==============================================================================
template
<
    typename Expr, typename F,
    typename = std::enable_if_t<!is_terminal<std::decay_t<Expr>>::value>
>
auto inorder_impl(Expr && e, F && f, int level)
{
    inorder_impl(e.left(), std::forward<F>(f), level + 1);
    f(std::forward<Expr>(e), level);
    inorder_impl(e.right(), std::forward<F>(f), level + 1);
}

template <typename T, typename F>
auto inorder_impl(terminal<T> & t, F && f, int level)
{
    f(*(t.derived()), level);
}

template <typename T, typename F>
auto inorder_impl(terminal<T> && t, F && f, int level)
{
    f(*(t.derived()), level);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e, F && f)
{
    inorder_impl(e, std::forward<F>(f), 0);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e, F && f)
{
    inorder_impl(std::move(e), std::forward<F>(f), 0);
}


//==============================================================================
template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto postorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e,
               F && f)
{
    postorder(e.left(), std::forward<F>(f));
    postorder(e.right(), std::forward<F>(f));
    f(e);
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto postorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e,
               F && f)
{
    postorder(e.left(), std::forward<F>(f));
    postorder(e.right(), std::forward<F>(f));
    f(std::forward<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>(e));
}

template <typename T, typename F>
auto postorder(terminal<T> & t, F && f)
{
    f(*(t.derived()));
}

template <typename T, typename F>
auto postorder(terminal<T> && t, F && f)
{
    f(*(t.derived()));
}


#endif // ROCKY_ET_TRAVERSAL_H
