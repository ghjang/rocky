#ifndef ROCKY_APP_REPLACE_H
#define ROCKY_APP_REPLACE_H


#include "rocky/base/TypeComposition.h"
#include "rocky/app/ReplaceIf.h"


template <typename SourceType, typename TargetType, typename... xs>
using ReplaceT = typename ReplaceIf<BindFirst<Quote<std::is_same>, SourceType>, TargetType, xs...>::type;


#endif //ROCKY_APP_REPLACE_H

