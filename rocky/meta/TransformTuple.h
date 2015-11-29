#ifndef ROCKY_TRANSFORMTUPLE_H
#define ROCKY_TRANSFORMTUPLE_H


// list comprehension


#include <array>
#include <tuple>
#include <utility>

#include "rocky/meta/IntegralConstantUtility.h"


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


//==============================================================================
// compiletime variable templates
//==============================================================================

template <typename Tuple, typename IndexSequence, std::size_t N = std::tuple_size<Tuple>::value>
constexpr std::array<bool, N> IntegralConstantElementTypeToBoolArrayImpl;

template <typename... list, std::size_t... i>
constexpr std::array<bool, sizeof...(list)> IntegralConstantElementTypeToBoolArrayImpl<
                                                    std::tuple<list...>,
                                                    std::index_sequence<i...>,
                                                    sizeof...(list)
                                            >{
        std::tuple_element_t<i, std::tuple<list...>>()...
};

template <typename Tuple, std::size_t N = std::tuple_size<Tuple>::value>
constexpr std::array<bool, N> IntegralConstantElementTypeToBoolArray;

template <typename... list>
constexpr std::array<bool, sizeof...(list)> IntegralConstantElementTypeToBoolArray<
                                                    std::tuple<list...>,
                                                    sizeof...(list)
                                            >{
        IntegralConstantElementTypeToBoolArrayImpl<std::tuple<list...>, std::index_sequence_for<list...>>
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
struct TransformToSequenceType;

template <typename... list>
struct TransformToSequenceType<std::tuple<list...>>
{
    constexpr static auto boolArray_ = IntegralConstantElementTypeToBoolArray<std::tuple<list...>>;

    template <typename IndexSequence>
    struct ConvertToIndexSequenceImpl;

    template <std::size_t... i>
    struct ConvertToIndexSequenceImpl<std::index_sequence<i...>>
    {
        using type = std::index_sequence<boolArray_[i]...>;
    };

    using type = typename ConvertToIndexSequenceImpl<std::make_index_sequence<sizeof...(list)>>::type;
};


#endif //ROCKY_TRANSFORMTUPLE_H

