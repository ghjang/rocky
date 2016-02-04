#ifndef ROCKY_WOLCA_NEST_H
#define ROCKY_WOLCA_NEST_H


#include <type_traits>

#include "rocky/base/Identity.h"


template <template <typename> class f, typename x, typename n>
struct Nest;

template <template <typename> class f, typename x, typename T>
struct Nest<f, x, std::integral_constant<T, 0>> : type_is<x>
{ };

template <template <typename> class f, typename x, typename T, T n>
struct Nest<f, x, std::integral_constant<T, n>>
        : Nest<f, typename f<x>::type, std::integral_constant<T, n - 1>>
{ };


template <template <typename> class f, typename x, std::size_t n>
using NestT = typename Nest<f, x, std::integral_constant<std::size_t, n>>::type;


#endif //ROCKY_WOLCA_NEST_H

