#ifndef ROCKY_TYPESELECTION_H
#define ROCKY_TYPESELECTION_H


#include "rocky/meta/Identity.h"
#include "rocky/meta/HasMember.h"


namespace Detail
{
    template <typename T>
    T SelectTypeIfImpl(...);

    template <typename T, typename = std::enable_if_t<HasTypeMember<T>::value>>
    typename T::type SelectTypeIfImpl(int);
} // namespace Detail


template <bool condition, typename T1, typename T2>
struct SelectTypeIf;

template <typename T1, typename T2>
struct SelectTypeIf<true, T1, T2>
        : type_is<decltype(Detail::SelectTypeIfImpl<T1>(int{}))>
{ };

template <typename T1, typename T2>
struct SelectTypeIf<false, T1, T2>
        : type_is<decltype(Detail::SelectTypeIfImpl<T2>(int{}))>
{ };


template <bool condition, typename T1, typename T2>
using SelectTypeIfT = typename SelectTypeIf<condition, T1, T2>::type;


#endif //ROCKY_TYPESELECTION_H

