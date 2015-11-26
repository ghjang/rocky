#ifndef ROCKY_TYPEUTILITY_H
#define ROCKY_TYPEUTILITY_H


#include "rocky/meta/Identity.h"


template <typename T>
constexpr IdentityType<T> type_c{};


template <typename T>
constexpr std::size_t TypeSizeOf(IdentityType<T>)
{ return sizeof(T); }


#endif //ROCKY_TYPEUTILITY_H

