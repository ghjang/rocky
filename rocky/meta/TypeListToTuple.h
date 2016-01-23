#ifndef ROCKY_TYPELISTTOTUPLE_H
#define ROCKY_TYPELISTTOTUPLE_H


#include <tuple>

#include "rocky/meta/Identity.h"
#include "rocky/meta/TypeList.h"


template <typename T>
struct TypeListToTuple;

template <typename... xs>
struct TypeListToTuple<TypeList<xs...>> : type_is<std::tuple<xs...>>
{ };


template <typename... xs>
using TypeListToTupleT = typename TypeListToTuple<xs...>::type;


#endif //ROCKY_TYPELISTTOTUPLE_H

