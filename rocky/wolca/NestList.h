#ifndef ROCKY_WOLCA_NESTLIST_H
#define ROCKY_WOLCA_NESTLIST_H


#include "rocky/base/TypeList.h"


namespace Detail
{
    template <template <typename> class f, typename x, typename n, typename rs>
    struct NestListImpl;

    template <template <typename> class f, typename x, typename T, typename... rs>
    struct NestListImpl<f, x, std::integral_constant<T, 0>, TypeList<rs...>>
            : type_is<TypeList<rs...>>
    { };

    template <template <typename> class f, typename x, typename T, T n, typename... rs>
    struct NestListImpl<f, x, std::integral_constant<T, n>, TypeList<rs...>>
            : NestListImpl<
                    f,
                    typename f<x>::type,
                    std::integral_constant<T, n - 1>,
                    TypeList<rs..., typename f<x>::type>
              >
    { };
} // namespace Detail


template <template <typename> class f, typename x, typename n>
struct NestList;

template <template <typename> class f, typename x, typename T, T n>
struct NestList<f, x, std::integral_constant<T, n>>
        : Detail::NestListImpl<f, x, std::integral_constant<T, n>, TypeList<x>>
{ };


template <template <typename> class f, typename x, std::size_t n>
using NestListT = typename NestList<f, x, std::integral_constant<std::size_t, n>>::type;


#endif //ROCKY_WOLCA_NESTLIST_H

