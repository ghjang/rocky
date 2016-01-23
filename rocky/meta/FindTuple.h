#ifndef ROCKY_FINDELEMENT_H
#define ROCKY_FINDELEMENT_H


#include "rocky/meta/IntegralConstantUtility.h"
#include "rocky/skull/Reverse.h"


template <typename T, typename... list>
struct FindElementType : FindElementType<T, int_c_t<0>, list...>
{ };

template <typename T, int i>
struct FindElementType<T, int_c_t<i>> : int_c_t<-1>
{ };

template <typename T, int i, typename... list>
struct FindElementType<T, int_c_t<i>, T, list...> : int_c_t<i>
{ };

template <typename T, typename U, int i, typename... list>
struct FindElementType<T, int_c_t<i>, U, list...> : FindElementType<T, int_c_t<i + 1>, list...>
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
                                    ReverseT<std::tuple<list...>>
                                >::value;

public:
    static constexpr int value = (i == -1) ? (-1) : (sizeof...(list) - i - 1);
};

template <typename T, typename... list>
struct ReverseFindElementType<T, std::tuple<list...>> : ReverseFindElementType<T, list...>
{ };


template <typename T, typename... list>
struct IsOneOf
        : std::conditional_t<
                FindElementType<T, list...>::value == -1,
                std::false_type,
                std::true_type
            >
{ };

template <typename T, typename... list>
struct IsOneOf<T, std::tuple<list...>> : IsOneOf<T, list...>
{ };


#endif //ROCKY_FINDELEMENT_H

