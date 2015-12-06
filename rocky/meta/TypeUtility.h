#ifndef ROCKY_TYPEUTILITY_H
#define ROCKY_TYPEUTILITY_H


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
struct CharPtrTypeToStrType
{
    using type = T;
};

template <std::size_t N>
struct CharPtrTypeToStrType<char [N]>
{
    using type = std::string;
};

template <std::size_t N>
struct CharPtrTypeToStrType<char const (&) [N]>
{
    using type = std::string;
};

template <>
struct CharPtrTypeToStrType<char const *>
{
    using type = std::string;
};

template <>
struct CharPtrTypeToStrType<char *>
{
    using type = std::string;
};

template <std::size_t N>
struct CharPtrTypeToStrType<wchar_t [N]>
{
    using type = std::wstring;
};

template <std::size_t N>
struct CharPtrTypeToStrType<wchar_t const (&) [N]>
{
    using type = std::wstring;
};

template <>
struct CharPtrTypeToStrType<wchar_t const *>
{
    using type = std::wstring;
};

template <>
struct CharPtrTypeToStrType<wchar_t *>
{
    using type = std::wstring;
};


#endif //ROCKY_TYPEUTILITY_H

