#ifndef ROCKY_BASE_HASMEMBER_H
#define ROCKY_BASE_HASMEMBER_H


#include <type_traits>


namespace Detail
{
    template<typename T, typename = typename T::type>
    std::true_type HasTypeMemberImpl(int);

    template<typename T>
    std::false_type HasTypeMemberImpl(...);
} // namespace Detail


template <typename T>
struct HasTypeMember : decltype(Detail::HasTypeMemberImpl<T>(int{}))
{ };


namespace Detail
{
    template<typename T, typename = decltype(T::value)>
    std::true_type HasValueMemberImpl(int);

    template<typename T>
    std::false_type HasValueMemberImpl(...);
} // namespace Detail


template <typename T>
struct HasValueMember : decltype(Detail::HasValueMemberImpl<T>(int{}))
{ };


namespace Detail
{
    template<typename T, template <typename...> class = T::template Apply>
    std::true_type HasApplyMemberImpl(int);

    template<typename T>
    std::false_type HasApplyMemberImpl(...);
} // namespace Detail


template <typename T>
struct HasApplyMember : decltype(Detail::HasApplyMemberImpl<T>(int{}))
{ };


#endif //ROCKY_BASE_HASMEMBER_H

