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

template <typename Tuple, template <typename> class F, typename IndexSequence>
struct TransformElementTypeImpl;

template <typename... list, template <typename> class F, std::size_t... i>
struct TransformElementTypeImpl<std::tuple<list...>, F, std::index_sequence<i...>>
{
    using type = std::tuple<typename F<std::tuple_element_t<i, std::tuple<list...>>>::type...>;
};

template <typename Tuple, template <typename> class F>
struct TransformElementType;

template <typename... list, template <typename> class F>
struct TransformElementType<std::tuple<list...>, F>
            : TransformElementTypeImpl<
                    std::tuple<list...>,
                    F,
                    std::index_sequence_for<list...>
                >
{
    static_assert(sizeof...(list) > 0, "tuple should have at least one template parameter.");
    static_assert(HasTypeMember<F<std::tuple_element_t<0, std::tuple<list...>>>>(), "F should have 'type' member.");
};


template <typename Tuple, template <typename> class Predicate>
struct TransformElementTypeToBoolConstantType
            : TransformElementType<
                    Tuple,
                    TypeToBoolConstantType<Predicate>::template Convert
                >
{
    static_assert(HasValueMember<Predicate<int>>(), "Predicate should have 'value' member.");
};


template <typename Tuple>
struct ConvertToIntegerSequenceType;

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
struct TransformBoolSequenceToTrueValueIndexSequence;

template <typename T, T... list>
struct TransformBoolSequenceToTrueValueIndexSequence<std::integer_sequence<T, list...>>
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
struct InvertBoolSequenceType;

template <typename T, T... i>
struct InvertBoolSequenceType<std::integer_sequence<T, i...>>
{
    using type = std::integer_sequence<T, (!i)...>;
};


//==============================================================================
// runtime functions
//==============================================================================

template <typename... list, typename F, std::size_t... i>
decltype(auto) TransformElementImpl(std::tuple<list...> const& t, F const& f, std::index_sequence<i...>)
{
    return std::make_tuple(f(std::get<i>(t))...);
}

template <typename... list, typename F>
decltype(auto) TransformElement(std::tuple<list...> const& t, F const& f)
{
    return TransformElementImpl(t, f, std::index_sequence_for<list...>{});
}


#endif //ROCKY_TRANSFORMTUPLE_H

