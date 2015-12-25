#ifndef ROCKY_TRANSFORMTUPLE_H
#define ROCKY_TRANSFORMTUPLE_H


// list comprehension


#include <array>
#include <tuple>
#include <utility>

#include "rocky/ConstExprArray.h"
#include "rocky/meta/IntegralConstantUtility.h"


//==============================================================================
// compiletime variable templates
//==============================================================================

template <typename Tuple, typename IndexSequence, std::size_t N = std::tuple_size<Tuple>::value>
constexpr std::array<int, N> IntegralConstantElementTypeToArrayImpl;

template <typename... list, std::size_t... i>
constexpr std::array<int, sizeof...(list)> IntegralConstantElementTypeToArrayImpl<
                                                std::tuple<list...>,
                                                std::index_sequence<i...>,
                                                sizeof...(list)
                                            >{
        std::tuple_element_t<i, std::tuple<list...>>()...
};

template <typename Tuple, std::size_t N = std::tuple_size<Tuple>::value>
constexpr std::array<int, N> IntegralConstantElementTypeToArray;

template <typename... list>
constexpr std::array<int, sizeof...(list)> IntegralConstantElementTypeToArray<
                                                std::tuple<list...>,
                                                sizeof...(list)
                                            >{
        IntegralConstantElementTypeToArrayImpl<std::tuple<list...>, std::index_sequence_for<list...>>
};


//==============================================================================
// compiletime metafunctions
//==============================================================================

namespace Detail
{
    template<template<typename> class F, typename Tuple, typename IndexSequence>
    struct TransformElementTypeImpl;

    template<template<typename> class F, typename... list, std::size_t... i>
    struct TransformElementTypeImpl<F, std::tuple<list...>, std::index_sequence<i...>>
    {
        using type = std::tuple<typename F<std::tuple_element_t<i, std::tuple<list...>>>::type...>;
    };
} // namespace Detail

template <template <typename> class F, typename Tuple>
struct TransformElementType;

template <template <typename> class F, typename... list>
struct TransformElementType<F, std::tuple<list...>>
            : Detail::TransformElementTypeImpl<
                    F,
                    std::tuple<list...>,
                    std::index_sequence_for<list...>
                >
{
    static_assert(sizeof...(list) > 0, "tuple should have at least one template parameter.");
    static_assert(HasTypeMember<F<std::tuple_element_t<0, std::tuple<list...>>>>(), "F should have 'type' member.");
};


template <template <typename> class Predicate, typename... list>
struct TransformElementTypeToBoolConstantType : TransformElementTypeToBoolConstantType<Predicate, std::tuple<list...>>
{ };

template <template <typename> class Predicate, typename... list>
struct TransformElementTypeToBoolConstantType<Predicate, std::tuple<list...>>
            : TransformElementType<
                    TypeToBoolConstantType<Predicate>::template Convert,
                    std::tuple<list...>
                >
{
    static_assert(HasValueMember<Predicate<int>>(), "Predicate should have 'value' member.");
};


template <typename... list>
struct ConvertToIntegerSequenceType : ConvertToIntegerSequenceType<std::tuple<list...>>
{ };

template <typename... list>
struct ConvertToIntegerSequenceType<std::tuple<list...>>
{
private:
    constexpr static auto array_ = IntegralConstantElementTypeToArray<std::tuple<list...>>;

    template <typename IndexSequence>
    struct ConvertToSequenceImpl;

    template <std::size_t... i>
    struct ConvertToSequenceImpl<std::index_sequence<i...>>
    {
        using array_element_type_t = std::decay_t<decltype(array_[0])>;
        using type = std::integer_sequence<array_element_type_t, array_[i]...>;
    };

public:
    using type = typename ConvertToSequenceImpl<std::make_index_sequence<sizeof...(list)>>::type;
};


template <typename BoolSequence>
struct ConvertBoolSequenceToTrueValueIndexSequence;

template <typename T, T... list>
struct ConvertBoolSequenceToTrueValueIndexSequence<std::integer_sequence<T, list...>>
{
private:
    constexpr static std::array<T, sizeof...(list)> array_ = { list... };

    constexpr static auto CountTrueValue()
    {
        T count = 0;
        for (int i = 0; i < array_.size(); ++i) {
            if (array_[i]) {
                ++count;
            }
        }
        return count;
    }

    constexpr static auto ConvertToTrueValueIndexArray()
    {
        constexpr auto count = CountTrueValue();
        ConstExprArray<T, count> result;
        int j = 0;
        for (int i = 0; i < array_.size(); ++i) {
            if (array_[i]) {
                result[j++] = i;
            }
        }
        return result;
    }

    constexpr static auto trueValueIndexArray_ = ConvertToTrueValueIndexArray();

    template <typename IndexSequence>
    struct ConvertToSequenceImpl;

    template <std::size_t... i>
    struct ConvertToSequenceImpl<std::index_sequence<i...>>
    {
        using array_element_type_t = std::decay_t<decltype(trueValueIndexArray_[0])>;
        using type = std::integer_sequence<array_element_type_t, trueValueIndexArray_[i]...>;
    };

public:
    using type = typename ConvertToSequenceImpl<std::make_index_sequence<trueValueIndexArray_.size()>>::type;
};


template <typename BoolSequence>
struct InvertBoolSequence;

template <typename T, T... i>
struct InvertBoolSequence<std::integer_sequence<T, i...>>
{
    using type = std::integer_sequence<T, (!i)...>;
};


template <typename IndexSequence, typename Tuple>
struct ExtractElementType;

template <typename T, T... i, typename... list>
struct ExtractElementType<std::integer_sequence<T, i...>, std::tuple<list...>>
{
    using type = std::tuple<std::tuple_element_t<i, std::tuple<list...>>...>;
};


//==============================================================================
// runtime functions
//==============================================================================

template <typename F, typename Tuple, std::size_t... i>
auto TransformElementImpl(F && f, Tuple && t, std::index_sequence<i...>)
{
    return std::make_tuple(f(std::get<i>(std::forward<Tuple>(t)))...);
}

template <typename F, typename... list>
auto TransformElement(F && f, std::tuple<list...> const& t)
{
    return TransformElementImpl(std::forward<F>(f), t, std::index_sequence_for<list...>{});
}

template <typename F, typename... list>
auto TransformElement(F && f, std::tuple<list...> && t)
{
    return TransformElementImpl(std::forward<F>(f), std::move(t), std::index_sequence_for<list...>{});
}


#endif //ROCKY_TRANSFORMTUPLE_H

