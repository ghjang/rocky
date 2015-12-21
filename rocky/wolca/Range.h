#ifndef ROCKY_WOLCA_RANGE_H
#define ROCKY_WOLCA_RANGE_H


#include <array>
#include <vector>
#include <utility>
#include <numeric>


template <int i>
struct RangeT
{
private:
    template <typename Indices>
    struct RangeTImpl;

    template <std::size_t... Indices>
    struct RangeTImpl<std::index_sequence<Indices...>>
    {
        static constexpr std::array<int, sizeof...(Indices)> value = { Indices... };
    };

public:
    static constexpr std::array<int, i> value = RangeTImpl<std::make_index_sequence<i>>::value;
};

template <int i>
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

