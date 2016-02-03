#ifndef ROCKY_APP_FIND_IF_H
#define ROCKY_APP_FIND_IF_H


#include "rocky/base/IntegralConstantUtility.h"
#include "rocky/skull/Reverse.h"


template <template <typename> class p, typename... xs>
struct FindIf : FindIf<p, int_c_t<0>, xs...>
{ };

template <template <typename> class p, int i>
struct FindIf<p, int_c_t<i>> : std::integral_constant<int, -1>
{ };

template <template <typename> class p, int i, typename x, typename... xs>
struct FindIf<p, int_c_t<i>, x, xs...>
        : SelectTypeIfT<
                p<x>::value,
                std::integral_constant<int, i>,
                FindIf<p, int_c_t<i + 1>, xs...>
          >
{
    static_assert(HasValueMember<p<x>>(), "Predicate 'p' should have value member.");
};


template <template <typename> class p, typename... xs>
struct FindIf<p, TypeList<xs...>> : FindIf<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct FindIf<p, std::tuple<xs...>> : FindIf<p, xs...>
{ };


template <template <typename> class p, typename... xs>
struct ReverseFindIf
{
private:
    static constexpr int i = FindIf<p, ReverseT<xs...>>();

public:
    static constexpr int value = (i == -1) ? (-1) : (sizeof...(xs) - i - 1);

    constexpr operator int () const noexcept { return value; }
};

template <template <typename> class p, typename... xs>
struct ReverseFindIf<p, TypeList<xs...>> : ReverseFindIf<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct ReverseFindIf<p, std::tuple<xs...>> : ReverseFindIf<p, xs...>
{ };


#endif //ROCKY_APP_FIND_IF_H

