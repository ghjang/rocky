#ifndef ROCKY_HASMEMBER_H
#define ROCKY_HASMEMBER_H


#include <type_traits>


template <typename T, typename = typename T::type>
std::true_type HasTypeMemberImpl(int);

template <typename T>
std::false_type HasTypeMemberImpl(...);

template <typename T>
struct HasTypeMember : decltype(HasTypeMemberImpl<T>(int{}))
{ };


template <typename T, typename = decltype(T::value)>
std::true_type HasValueMemberImpl(int);

template <typename T>
std::false_type HasValueMemberImpl(...);

template <typename T>
struct HasValueMember : decltype(HasValueMemberImpl<T>(int{}))
{ };


#endif //ROCKY_HASMEMBER_H

