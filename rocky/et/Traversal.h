#ifndef ROCKY_ET_TRAVERSAL_H
#define ROCKY_ET_TRAVERSAL_H


template<typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct expression;

template <typename Derived>
struct terminal;


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e,
              F && f)
{
    f(e);
    preorder(e.left(), std::forward<F>(f));
    preorder(e.right(), std::forward<F>(f));
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto preorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e,
              F && f)
{
    f(std::forward<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>(e));
    preorder(e.left(), std::forward<F>(f));
    preorder(e.right(), std::forward<F>(f));
}

template <typename T, typename F>
auto preorder(terminal<T> & t, F && f)
{
    f(*(t.derived()));
}

template <typename T, typename F>
auto preorder(terminal<T> && t, F && f)
{
    f(*(t.derived()));
}


template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> & e,
             F && f)
{
    inorder(e.left(), std::forward<F>(f));
    f(e);
    inorder(e.right(), std::forward<F>(f));
}

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    typename F
>
auto inorder(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef> && e,
             F && f)
{
    inorder(e.left(), std::forward<F>(f));
    f(std::forward<expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef>>(e));
    inorder(e.right(), std::forward<F>(f));
}

template <typename T, typename F>
auto inorder(terminal<T> & t, F && f)
{
    f(*(t.derived()));
}

template <typename T, typename F>
auto inorder(terminal<T> && t, F && f)
{
    f(*(t.derived()));
}


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
