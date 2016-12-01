#ifndef ROCKY_ET_FOLD_H
#define ROCKY_ET_FOLD_H


#include <array>

#define ROCKY_ET_OPERATION_POLICY fold_functor
#include "rocky/et/ExpressionTemplate.h"
#include "rocky/et/PlaceHolderDef.h"


//==============================================================================
template <typename F, typename T, typename... Args>
auto foldl_impl(F && f, T && init, Args &&... args)
{
    // NOTE: clang bug? had to surround the fold expression to fix compiler error.
    return ((... + args))(std::forward<F>(f), std::forward<T>(init));
}

template <typename F, typename T, std::size_t n, std::size_t... i>
auto foldl_impl(F && f, T && init, std::array<T, n> & a, std::index_sequence<i...>)
{
    return foldl_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                _1, // append to the FIRST to make expression tree
                std::get<i>(a)...
           );
}

template <typename F, typename T, typename... Args>
auto foldl(F && f, T && init, Args &&... args)
{
    return foldl_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                _1, // append to the FIRST to make expression tree
                std::forward<Args>(args)...
           );
}

template <typename F, typename T, std::size_t n>
auto foldl(F && f, T && init, std::array<T, n> & a)
{
    return foldl_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                a,
                std::make_index_sequence<n>{}
           );
}

template <typename... Args>
auto foldl_expr_impl(Args &&... args)
{
    return (... + args);
}

template <typename... Args>
auto foldl_expr(Args &&... args)
{
    return foldl_expr_impl(_1, std::forward<Args>(args)...);
}


//==============================================================================
template <typename F, typename T, typename... Args>
auto foldr_impl(F && f, T && init, Args &&... args)
{
    return (args + ...)(std::forward<F>(f), std::forward<T>(init));
}

template <typename F, typename T, std::size_t n, std::size_t... i>
auto foldr_impl(F && f, T && init, std::array<T, n> & a, std::index_sequence<i...>)
{
    return foldr_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                std::get<i>(a)...,
                _1 // append to the LAST to make expression tree
           );
}

template <typename F, typename T, typename... Args>
auto foldr(F && f, T && init, Args &&... args)
{
    return foldr_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                std::forward<Args>(args)...,
                _1  // append to the LAST to make expression tree
           );
}

template <typename F, typename T, std::size_t n>
auto foldr(F && f, T && init, std::array<T, n> & a)
{
    return foldr_impl(
                std::forward<F>(f),
                std::forward<T>(init),
                a,
                std::make_index_sequence<n>{}
           );
}

template <typename... Args>
auto foldr_expr_impl(Args &&... args)
{
    return (args + ...);
}

template <typename... Args>
auto foldr_expr(Args &&... args)
{
    return foldr_expr_impl(std::forward<Args>(args)..., _1);
}


#endif // ROCKY_ET_FOLD_H
