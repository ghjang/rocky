#ifndef ROCKY_TYPESELECTION_H
#define ROCKY_TYPESELECTION_H


#include <type_traits>

#include "rocky/HasTypeMember.h"


template <typename T>
T SelectTypeIfImpl(...);

template <typename T, typename = std::enable_if_t<HasTypeMember<T>::value>>
typename T::type SelectTypeIfImpl(int);


template <typename boolConstant, typename T1, typename T2>
struct SelectTypeIf;

template <typename T1, typename T2>
struct SelectTypeIf<std::true_type, T1, T2>
{
    using type = decltype(SelectTypeIfImpl<T1>(int{}));
};

template <typename T1, typename T2>
struct SelectTypeIf<std::false_type, T1, T2>
{
    using type = decltype(SelectTypeIfImpl<T2>(int{}));
};


#endif //ROCKY_TYPESELECTION_H

