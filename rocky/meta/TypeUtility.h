#ifndef ROCKY_TYPEUTILITY_H
#define ROCKY_TYPEUTILITY_H


#include "rocky/meta/Identity.h"


/**
 * For type displaying.
 */
template <typename T>
struct TD;


template <typename T>
constexpr Identity<T> type_c{};


template <typename T>
constexpr std::size_t TypeSizeOf(Identity<T>)
{ return sizeof(T); }


#endif //ROCKY_TYPEUTILITY_H

