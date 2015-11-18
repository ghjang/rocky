#ifndef ROCKY_HASTYPEMEMBER_H
#define ROCKY_HASTYPEMEMBER_H


#include <type_traits>


template <typename T, typename = typename T::type>
std::true_type HasTypeMemberImpl(int);

template <typename T>
std::false_type HasTypeMemberImpl(...);

template <typename T>
struct HasTypeMember : decltype(HasTypeMemberImpl<T>(int{}))
{ };


#endif //ROCKY_HASTYPEMEMBER_H

