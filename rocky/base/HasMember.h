#ifndef ROCKY_BASE_HASMEMBER_H
#define ROCKY_BASE_HASMEMBER_H


#include <type_traits>

#include "rocky/base/VoidT.h"


template <typename T, typename = void>
struct HasTypeMember : std::false_type
{ };

template <typename T>
struct HasTypeMember<T, void_t<typename T::type>> : std::true_type
{ };


template <typename T, typename = void>
struct HasValueMember : std::false_type
{ };

template <typename T>
struct HasValueMember<T, void_t<decltype (T::value)>> : std::true_type
{ };


template <typename T, typename = void>
struct HasApplyMember : std::false_type
{ };

template <typename T>
struct HasApplyMember<T, void_template_t<T::template Apply>> : std::true_type
{ };


#endif //ROCKY_BASE_HASMEMBER_H

