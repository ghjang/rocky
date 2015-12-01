#ifndef ROCKY_REPLACETUPLE_H
#define ROCKY_REPLACETUPLE_H


#include "rocky/meta/TransformTuple.h"


template <typename Tuple, typename SourceType, typename TargetType>
struct ReplaceElementType;

template <typename... list, typename SourceType, typename TargetType>
struct ReplaceElementType<std::tuple<list...>, SourceType, TargetType>
{
private:
    template <typename T>
    struct SourceTypeToTargetType
                : SelectTypeIf<
                        std::is_same<T, SourceType>::value,
                        TargetType,
                        T
                    >
    { };

public:
    using type = typename TransformElementType<std::tuple<list...>, SourceTypeToTargetType>::type;
};


#endif //ROCKY_REPLACETUPLE_H
