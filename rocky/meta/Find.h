#ifndef ROCKY_FIND_H
#define ROCKY_FIND_H


#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/Reverse.h"


template <typename T, typename... xs>
struct Find : Find<T, int_c_t<0>, xs...>
{ };

template <typename T, int i>
struct Find<T, int_c_t<i>> : int_c_t<-1>
{ };

template <typename T, int i, typename... xs>
struct Find<T, int_c_t<i>, T, xs...> : int_c_t<i>
{ };

template <typename T, typename U, int i, typename... xs>
struct Find<T, int_c_t<i>, U, xs...> : Find<T, int_c_t<i + 1>, xs...>
{ };


template <typename T, typename... xs>
struct Find<T, TypeList<xs...>> : Find<T, xs...>
{ };

template <typename T, typename... xs>
struct Find<T, std::tuple<xs...>> : Find<T, xs...>
{ };


template <typename T, typename... xs>
struct ReverseFind
{
private:
    static constexpr int i = Find<T, ReverseT<std::tuple<xs...>>>::value;

public:
    static constexpr int value = (i == -1) ? (-1) : (sizeof...(xs) - i - 1);

    constexpr operator int () const noexcept { return value; }
};

template <typename T, typename... xs>
struct ReverseFind<T, TypeList<xs...>> : ReverseFind<T, xs...>
{ };

template <typename T, typename... xs>
struct ReverseFind<T, std::tuple<xs...>> : ReverseFind<T, xs...>
{ };


#endif //ROCKY_FIND_H

