#ifndef ROCKY_ET_STORAGE_POLICY_H
#define ROCKY_ET_STORAGE_POLICY_H


#include "rocky/et/ExpressionTemplateFwd.h"


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct default_storage;

template <typename Left, typename Right>
struct default_storage<Left, Right, false, false>
{
    Left & left_;
    Right & right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};

template <typename Left, typename Right>
struct default_storage<Left, Right, false, true>
{
    Left & left_;
    Right right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};

template <typename Left, typename Right>
struct default_storage<Left, Right, true, false>
{
    Left left_;
    Right & right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};

template <typename Left, typename Right>
struct default_storage<Left, Right, true, true>
{
    Left left_;
    Right right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct value_storage
{
    Left left_;
    Right right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};

template 
<
    bool IsValRValRef, typename T,
    typename Right, bool IsLeftRValRef, bool IsRightRValRef
>
struct value_storage
<
    value_holder<IsValRValRef, T>, Right, IsLeftRValRef, IsRightRValRef
>
{
    value_holder<true, T> left_;
    Right right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};

template 
<
    bool IsValRValRef, typename T,
    typename Left, bool IsLeftRValRef, bool IsRightRValRef
>
struct value_storage
<
    Left, value_holder<IsValRValRef, T>, IsLeftRValRef, IsRightRValRef
>
{
    Left left_;
    value_holder<true, T> right_;

    auto & left()  { return left_; }
    auto & right() { return right_; }
};


#endif // ROCKY_ET_STORAGE_POLICY_H
