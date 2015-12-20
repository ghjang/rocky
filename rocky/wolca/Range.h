#ifndef ROCKY_WOLCA_RANGE_H
#define ROCKY_WOLCA_RANGE_H


#include <array>
#include <vector>
#include <utility>
#include <numeric>


template <typename Indices>
struct RangeTImpl;

template <std::size_t... i>
struct RangeTImpl<std::index_sequence<i...>>
{
    static constexpr std::array<int, sizeof...(i)> value = { i... };
};

template <std::size_t i>
struct RangeT
{
    static constexpr std::array<int, i> value = RangeTImpl<std::make_index_sequence<i>>::value;
};

template <std::size_t i>
constexpr std::array<int, i> RangeT<i>::value;


template <std::size_t... Indices>
constexpr auto RangeImpl(std::index_sequence<Indices...>)
{
    return std::array<int, sizeof...(Indices)>{ Indices... };
}

template <int i>
constexpr auto Range()
{
    return RangeImpl(std::make_index_sequence<i>());
}


auto Range(int const i)
{
    std::vector<int> rv(i);
    std::iota(rv.begin(), rv.end(), 0);
    return rv;
}


#endif //ROCKY_WOLCA_RANGE_H

