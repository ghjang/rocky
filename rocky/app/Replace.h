#ifndef ROCKY_APP_REPLACE_H
#define ROCKY_APP_REPLACE_H


#include "rocky/base/TypeUtility.h"
#include "rocky/app/ReplaceIf.h"


template <typename SourceType, typename TargetType, typename... xs>
using ReplaceT = typename ReplaceIf<Bind1st<std::is_same, SourceType>::template Convert, TargetType, xs...>::type;


#endif //ROCKY_APP_REPLACE_H

