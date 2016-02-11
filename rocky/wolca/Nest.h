#ifndef ROCKY_WOLCA_NEST_H
#define ROCKY_WOLCA_NEST_H


#include <type_traits>

#include "rocky/base/Identity.h"
#include "rocky/base/TypeUtility.h"


/**
 * @tparam f metafunction class
 */
template <typename f, typename x, typename n>
struct Nest;

template <typename f, typename x, typename T>
struct Nest<f, x, std::integral_constant<T, 0>> : type_is<x>
{ };

template <typename f, typename x, typename T, T n>
struct Nest<f, x, std::integral_constant<T, n>>
        : Nest<f, typename ApplyT<f, x>::type, std::integral_constant<T, n - 1>>
{ };


template <typename f, typename x, std::size_t n>
using NestT = typename Nest<f, x, std::integral_constant<std::size_t, n>>::type;


#endif //ROCKY_WOLCA_NEST_H

