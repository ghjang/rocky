#ifndef ROCKY_TRANSFORMTUPLE_H
#define ROCKY_TRANSFORMTUPLE_H


// list comprehension


#include <array>
#include <tuple>
#include <utility>

#include "rocky/ConstExprArray.h"
#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/TypeList.h"
#include "rocky/meta/TypeListToTuple.h"
#include "rocky/skull/Head.h"
#include "rocky/skull/Map.h"


//==============================================================================
// compiletime variable templates
//==============================================================================

namespace Detail
{
    template <typename Tuple, typename IndexSequence, std::size_t N = std::tuple_size<Tuple>::value>
    constexpr std::array<int, N> IntegralConstantElementTypeToArrayImpl;

    template <typename... list, std::size_t... i>
    constexpr std::array<int, sizeof...(list)> IntegralConstantElementTypeToArrayImpl<
                                                        std::tuple<list...>,
                                                        std::index_sequence<i...>,
                                                        sizeof...(list)
                                                >{ std::tuple_element_t<i, std::tuple<list...>>()... };
} // namespace Detail

template <typename Tuple, std::size_t N = std::tuple_size<Tuple>::value>
constexpr std::array<int, N> IntegralConstantElementTypeToArray;

template <typename... list>
constexpr std::array<int, sizeof...(list)> IntegralConstantElementTypeToArray<
                                                std::tuple<list...>,
                                                sizeof...(list)
                                            >{
        Detail::IntegralConstantElementTypeToArrayImpl<std::tuple<list...>, std::index_sequence_for<list...>>
};


//==============================================================================
// compiletime metafunctions
//==============================================================================
template <template <typename> class p, typename... xs>
struct MapToBoolConstantType : Map<TypeToBoolConstantType<p>::template Convert, xs...>
{
    static_assert(HasValueMember<p<HeadT<xs...>>>(), "Predicate p should have 'value' member.");
};

template <template <typename> class p, typename... xs>
using MapToBoolConstantTypeT = typename MapToBoolConstantType<p, xs...>::type;


template <template <typename> class p, typename... xs>
struct MapToBoolConstantType<p, TypeList<xs...>> : MapToBoolConstantTypeT<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct MapToBoolConstantType<p, std::tuple<xs...>> : TypeListToTuple<MapToBoolConstantTypeT<p, xs...>>
{ };


template <typename... list>
struct MapToIntegerSequenceType : MapToIntegerSequenceType<std::tuple<list...>>
{ };

template <typename... list>
struct MapToIntegerSequenceType<std::tuple<list...>>
{
private:
    constexpr static auto array_ = IntegralConstantElementTypeToArray<std::tuple<list...>>;

    template <typename IndexSequence>
    struct MapToSequenceImpl;

    template <std::size_t... i>
    struct MapToSequenceImpl<std::index_sequence<i...>>
    {
        using array_element_type_t = std::decay_t<decltype(array_[0])>;
        using type = std::integer_sequence<array_element_type_t, array_[i]...>;
    };

public:
    using type = typename MapToSequenceImpl<std::make_index_sequence<sizeof...(list)>>::type;
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


//==============================================================================
// runtime functions
//==============================================================================

namespace Detail
{
    template<typename F, typename Tuple, std::size_t... i>
    auto TransformElementImpl(F &&f, Tuple &&t, std::index_sequence<i...>)
    {
        return std::make_tuple(f(std::get<i>(std::forward<Tuple>(t)))...);
    }
} // namespace Detail


template <typename F, typename... list>
auto TransformElement(F && f, std::tuple<list...> const& t)
{
    return Detail::TransformElementImpl(std::forward<F>(f), t, std::index_sequence_for<list...>{});
}

template <typename F, typename... list>
auto TransformElement(F && f, std::tuple<list...> && t)
{
    return Detail::TransformElementImpl(std::forward<F>(f), std::move(t), std::index_sequence_for<list...>{});
}


#endif //ROCKY_TRANSFORMTUPLE_H

