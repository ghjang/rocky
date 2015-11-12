#ifndef ROCKY_TYPESELECTION_H
#define ROCKY_TYPESELECTION_H


#include <type_traits>


template <typename boolConstant, typename T1, typename T2>
struct SelectTypeIf;

template <typename T1, typename T2>
struct SelectTypeIf<std::integral_constant<bool, true>, T1, T2>
{
    using type = T1;
};

template <typename T1, typename T2>
struct SelectTypeIf<std::integral_constant<bool, false>, T1, T2>
{
    using type = T2;
};


#endif //ROCKY_TYPESELECTION_H

