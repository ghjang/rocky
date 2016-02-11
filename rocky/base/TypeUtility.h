#ifndef ROCKY_BASE_TYPEUTILITY_H
#define ROCKY_BASE_TYPEUTILITY_H


#include "rocky/base/Identity.h"
#include "rocky/base/IntegralConstantUtility.h"


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
struct IsCharType : bool_c_t<std::is_same<T, char>::value || std::is_same<T, wchar_t>::value>
{ };


template <typename T, typename = void>
struct CharTypeToStringType : type_is<T>
{ };

template <typename T, std::size_t N>
struct CharTypeToStringType<T [N], std::enable_if_t<IsCharType<T>::value>>
        : type_is<std::basic_string<T>>
{ };

template <typename T, std::size_t N>
struct CharTypeToStringType<T const (&) [N], std::enable_if_t<IsCharType<T>::value>>
        : type_is<std::basic_string<T>>
{ };

template <typename T>
struct CharTypeToStringType<T *, std::enable_if_t<IsCharType<T>::value>>
        : type_is<std::basic_string<T>>
{ };

template <typename T>
struct CharTypeToStringType<T const *, std::enable_if_t<IsCharType<T>::value>>
        : type_is<std::basic_string<T>>
{ };

template <typename T>
using CharTypeToStringTypeT = typename CharTypeToStringType<T>::type;


template <typename f, typename... xs>
using ApplyT = typename f::template Apply<xs...>;

template <template <typename...> class f>
struct Quote
{
    template <typename... xs>
    using Apply = f<xs...>;
};


/**
 * NegatePredicate itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam Predicate metafunction class
 */
template <typename Predicate>
struct NegatePredicate
{
    template <typename T>
    struct Apply : std::integral_constant<bool, !ApplyT<Predicate, T>::value>
    { };
};

/**
 * Bind1st is itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam BinaryF metafunction class
 */
template <typename BinaryF, typename T>
struct Bind1st
{
    template <typename V>
    struct Apply : ApplyT<BinaryF, T, V>
    { };
};

/**
 * Bind2nd is itself is a metafunction class and also a kind of high-order metafunction.
 *
 * @tparam BinaryF metafunction class
 */
template <typename BinaryF, typename T>
struct Bind2nd
{
    template <typename V>
    struct Apply : ApplyT<BinaryF, V, T>
    { };
};


#endif //ROCKY_BASE_TYPEUTILITY_H

