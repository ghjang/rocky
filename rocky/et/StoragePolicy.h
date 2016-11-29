#ifndef ROCKY_ET_STORAGE_POLICY_H
#define ROCKY_ET_STORAGE_POLICY_H


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct default_storage;

template <typename Left, typename Right>
struct default_storage<Left, Right, false, false>
{
    Left & left_;
    Right & right_;
};

template <typename Left, typename Right>
struct default_storage<Left, Right, false, true>
{
    Left & left_;
    Right right_;
};

template <typename Left, typename Right>
struct default_storage<Left, Right, true, false>
{
    Left left_;
    Right & right_;
};

template <typename Left, typename Right>
struct default_storage<Left, Right, true, true>
{
    Left left_;
    Right right_;
};


//==============================================================================
template<typename Left, typename Right, bool IsLeftRValRef, bool IsRightRValRef>
struct value_storage
{
    Left left_;
    Right right_;
};


#endif // ROCKY_ET_STORAGE_POLICY_H
