#ifndef ROCKY_APP_FIND_H
#define ROCKY_APP_FIND_H


#include "rocky/base/TypeComposition.h"
#include "rocky/app/FindIf.h"
#include "rocky/skull/Reverse.h"


template <typename T, typename... xs>
struct Find : FindIf<BindFirst<Quote<std::is_same>, T>, xs...>
{ };


template <typename T, typename... xs>
struct Find<T, TypeList<xs...>> : Find<T, xs...>
{ };

template <typename T, typename... xs>
struct Find<T, std::tuple<xs...>> : Find<T, xs...>
{ };


template <typename T, typename... xs>
struct ReverseFind : ReverseFindIf<BindFirst<Quote<std::is_same>, T>, xs...>
{ };


template <typename T, typename... xs>
struct ReverseFind<T, TypeList<xs...>> : ReverseFind<T, xs...>
{ };

template <typename T, typename... xs>
struct ReverseFind<T, std::tuple<xs...>> : ReverseFind<T, xs...>
{ };


#endif //ROCKY_APP_FIND_H

