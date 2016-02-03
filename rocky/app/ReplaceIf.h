#ifndef ROCKY_APP_REPLACEIF_H
#define ROCKY_APP_REPLACEIF_H


#include "rocky/app/Transform.h"


template <template <typename> class p, typename TargetType, typename... xs>
struct ReplaceIf
{
private:
    template <typename T>
    struct SourceTypeToTargetType
                : std::conditional<
                        p<T>::value,
                        TargetType,
                        T
                    >
    {
        static_assert(HasValueMember<p<TargetType>>(), "Predicate 'p' should have value member.");
    };

public:
    using type = MapT<SourceTypeToTargetType, xs...>;
};


template <template <typename> class p, typename TargetType, typename... xs>
using ReplaceIfT = typename ReplaceIf<p, TargetType, xs...>::type;


template <template <typename> class p, typename TargetType, typename... xs>
struct ReplaceIf<p, TargetType, TypeList<xs...>> : ReplaceIf<p, TargetType, xs...>
{ };

template <template <typename> class p, typename TargetType, typename... xs>
struct ReplaceIf<p, TargetType, std::tuple<xs...>> : TypeListToTuple<ReplaceIfT<p, TargetType, xs...>>
{ };


#endif //ROCKY_APP_REPLACEIF_H

