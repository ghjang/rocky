#ifndef ROCKY_TUPLESIZE_H
#define ROCKY_TUPLESIZE_H


#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/meta/ReverseTuple.h"


template <typename T, typename... list>
struct FindElementType : FindElementType<T, int_c_t<0>, list...>
{ };

template <typename T, int I>
struct FindElementType<T, int_c_t<I>> : int_c_t<-1>
{ };

template <typename T, int I, typename... list>
struct FindElementType<T, int_c_t<I>, T, list...> : int_c_t<I>
{ };

template <typename T, typename U, int I, typename... list>
struct FindElementType<T, int_c_t<I>, U, list...> : FindElementType<T, int_c_t<I + 1>, list...>
{ };

template <typename T, typename... list>
struct FindElementType<T, std::tuple<list...>> : FindElementType<T, list...>
{ };


template <typename T, typename... list>
struct ReverseFindElementType
{
private:
    static constexpr int i = FindElementType<
                                    T,
                                    typename ReverseElementType<std::tuple<list...>>::type
                                >::value;

public:
    static constexpr int value = (i == -1) ? (-1) : (sizeof...(list) - i - 1);
};

template <typename T, typename... list>
struct ReverseFindElementType<T, std::tuple<list...>> : ReverseFindElementType<T, list...>
{ };


template <typename T, typename... list>
struct IsOneOf;

template <typename T>
struct IsOneOf<T> : std::false_type
{ };

template <typename T, typename... list>
struct IsOneOf<T, T, list...> : std::true_type
{ };

template <typename T, typename U, typename... list>
struct IsOneOf<T, U, list...> : IsOneOf<T, list...>
{ };

template <typename T, typename... list>
struct IsOneOf<T, std::tuple<list...>> : IsOneOf<T, list...>
{ };


#endif //ROCKY_TUPLESIZE_H

