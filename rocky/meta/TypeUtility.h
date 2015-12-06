#ifndef ROCKY_TYPEUTILITY_H
#define ROCKY_TYPEUTILITY_H


#include <type_traits>

#include "rocky/meta/Identity.h"


/**
 * For type displaying.
 */
template <typename T>
struct TD;


template <typename T>
constexpr Identity<T> type_c{};


template <typename T>
constexpr std::size_t TypeSizeOf(Identity<T>)
{ return sizeof(T); }


template <typename T>
struct IsCharType
        : std::integral_constant<bool, std::is_same<T, char>::value || std::is_same<T, wchar_t>::value>
{ };


template <typename T, typename = void>
struct CharPtrTypeToStrType
{
    using type = T;
};

template <typename T, std::size_t N>
struct CharPtrTypeToStrType<T [N], std::enable_if_t<IsCharType<T>::value>>
{
    using type = std::basic_string<T>;
};

template <typename T, std::size_t N>
struct CharPtrTypeToStrType<T const (&) [N], std::enable_if_t<IsCharType<T>::value>>
{
    using type = std::basic_string<T>;
};

template <typename T>
struct CharPtrTypeToStrType<T *, std::enable_if_t<IsCharType<T>::value>>
{
    using type = std::basic_string<T>;
};

template <typename T>
struct CharPtrTypeToStrType<T const *, std::enable_if_t<IsCharType<T>::value>>
{
    using type = std::basic_string<T>;
};


#endif //ROCKY_TYPEUTILITY_H

