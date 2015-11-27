#ifndef ROCKY_FOREACHTUPLEELEMENTTYP_H
#define ROCKY_FOREACHTUPLEELEMENTTYP_H


#include <tuple>
#include <utility>

#include "rocky/meta/ForEachArgument.h"
#include "rocky/meta/TypeUtility.h"


template <typename F, typename... Type>
decltype(auto) ForEachTupleElementType(F && f, std::tuple<Type...> &&)
{
    return ForEachArgument(std::forward<F>(f), type_c<Type>...);
}


#endif //ROCKY_FOREACHTUPLEELEMENTTYP_H

