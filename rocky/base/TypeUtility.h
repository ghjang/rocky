#ifndef ROCKY_BASE_TYPEUTILITY_H
#define ROCKY_BASE_TYPEUTILITY_H


#include "rocky/base/Identity.h"
#include "rocky/base/HasMember.h"


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
        : std::integral_constant<
                bool,
                std::is_same<T, char>::value || std::is_same<T, wchar_t>::value
          >
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


/**
 * Quote itself is a helper metafunction class and also a high-order metafunction
 * which turns metafunctions into metafunction classes.
 */
template <template <typename...> class f>
struct Quote
{
    template <typename... xs>
    struct Apply : f<xs...>
    { };
};


/**
 *
 */
template <typename f, typename... xs>
struct Apply
{
    // NOTE: This assertion is redundant. No 'Apply' member existence in f will results in a compile error.
    //       But, I just wanted to show more understandable error message.
    static_assert(HasApplyMember<f>(), "metafunction class f should have 'Apply' member class template.");

    using type = typename f::template Apply<xs...>;
};

/**
 * type alias for ease use of applying metafunction classes
 */
template <typename f, typename... xs>
using ApplyT = typename Apply<f, xs...>::type;


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

