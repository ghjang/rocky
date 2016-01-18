#ifndef ROCKY_SKULL_HEAD_H
#define ROCKY_SKULL_HEAD_H


#include "rocky/meta/Identity.h"


template <typename... T>
struct Head
{
    static_assert(sizeof...(T) > 0, "empty type list is not allowed.");
};

template <typename head, typename... tail>
struct Head<head, tail...> : type_is<head>
{ };


#endif //ROCKY_SKULL_HEAD_H

