#ifndef ROCKY_BASE_REPLACETUPLE_H
#define ROCKY_BASE_REPLACETUPLE_H


#include "rocky/base/Transform.h"


template <typename SourceType, typename TargetType, typename... xs>
struct Replace
{
private:
    template <typename T>
    struct SourceTypeToTargetType
                : std::conditional<
                        std::is_same<T, SourceType>::value,
                        TargetType,
                        T
                    >
    { };

public:
    using type = MapT<SourceTypeToTargetType, xs...>;
};


template <typename SourceType, typename TargetType, typename... xs>
using ReplaceT = typename Replace<SourceType, TargetType, xs...>::type;


template <typename SourceType, typename TargetType, typename... xs>
struct Replace<SourceType, TargetType, TypeList<xs...>> : Replace<SourceType, TargetType, xs...>
{ };

template <typename SourceType, typename TargetType, typename... xs>
struct Replace<SourceType, TargetType, std::tuple<xs...>> : TypeListToTuple<ReplaceT<SourceType, TargetType, xs...>>
{ };


#endif //ROCKY_BASE_REPLACETUPLE_H

