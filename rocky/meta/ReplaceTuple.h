#ifndef ROCKY_REPLACETUPLE_H
#define ROCKY_REPLACETUPLE_H


#include "rocky/meta/Transform.h"


template <typename SourceType, typename TargetType, typename Tuple>
struct ReplaceElementType;

template <typename SourceType, typename TargetType, typename... list>
struct ReplaceElementType<SourceType, TargetType, std::tuple<list...>>
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
    using type = MapT<SourceTypeToTargetType, std::tuple<list...>>;
};


#endif //ROCKY_REPLACETUPLE_H

