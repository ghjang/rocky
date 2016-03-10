#ifndef ROCKY_BASE_ARRAYUTILITY_H
#define ROCKY_BASE_ARRAYUTILITY_H


#include <type_traits>
#include <array>

#include "rocky/base/Identity.h"


template <std::size_t... i>
using array_extents_t = std::integer_sequence<std::size_t, i...>;


namespace Detail
{
    template <typename ArrayExtentsSequence, typename T>
    struct AllExtentsImpl;

    template <std::size_t... i, typename T>
    struct AllExtentsImpl<array_extents_t<i...>, T> : type_is<array_extents_t<i...>>
    { };

    template <std::size_t... i, typename T, std::size_t N>
    struct AllExtentsImpl<array_extents_t<i...>, T[N]> : AllExtentsImpl<array_extents_t<i..., N>, T>
    { };
} // namespace Detail


template <typename T>
struct AllExtents
{
    static_assert(std::is_array<T>(), "T should be an array.");
};

template <typename T>
struct AllExtents<T[]> : Detail::AllExtentsImpl<array_extents_t<0>, T>
{ };

template <typename T, std::size_t N>
struct AllExtents<T[N]> : Detail::AllExtentsImpl<array_extents_t<N>, T>
{ };


template <typename T>
using AllExtentsT = typename AllExtents<T>::type;


namespace Detail
{
    template <std::size_t... i>
    constexpr auto allExtentsImpl(array_extents_t<i...>)
    {
        return std::array<std::size_t, sizeof...(i)>{ i... };
    }
} // namespace Detail

template <typename T>
constexpr auto allExtents()
{
    return Detail::allExtentsImpl(AllExtentsT<T>());
}


#endif //ROCKY_BASE_ARRAYUTILITY_H

