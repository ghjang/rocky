#ifndef ROCKY_TYPESELECTION_H
#define ROCKY_TYPESELECTION_H


#include <type_traits>

#include "rocky/meta/HasMember.h"


template <typename T>
T SelectTypeIfImpl(...);

template <typename T, typename = std::enable_if_t<HasTypeMember<T>::value>>
typename T::type SelectTypeIfImpl(int);


template <bool condition, typename T1, typename T2>
struct SelectTypeIf;

template <typename T1, typename T2>
struct SelectTypeIf<true, T1, T2>
{
    using type = decltype(SelectTypeIfImpl<T1>(int{}));
};

template <typename T1, typename T2>
struct SelectTypeIf<false, T1, T2>
{
    using type = decltype(SelectTypeIfImpl<T2>(int{}));
};


template <bool condition, typename T1, typename T2>
struct SelectParameterTypeIf;

template <typename T1, typename T2>
struct SelectParameterTypeIf<true, T1, T2>
{
    using type = T1;
};

template <typename T1, typename T2>
struct SelectParameterTypeIf<false, T1, T2>
{
    using type = T2;
};


#endif //ROCKY_TYPESELECTION_H

