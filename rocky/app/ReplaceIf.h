#ifndef ROCKY_APP_REPLACEIF_H
#define ROCKY_APP_REPLACEIF_H


#include "rocky/base/TypeUtility.h"
#include "rocky/app/Transform.h"


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename TargetType, typename... xs>
struct ReplaceIf
{
private:
    template <typename T>
    struct SourceTypeToTargetType
                : std::conditional<
                        ApplyT<p, T>::value,
                        TargetType,
                        T
                    >
    {
        static_assert(HasValueMember<ApplyT<p, TargetType>>(), "applied predicate 'p' should have value member.");
    };

public:
    using type = MapT<Quote<SourceTypeToTargetType>, xs...>;
};


template <typename p, typename TargetType, typename... xs>
using ReplaceIfT = typename ReplaceIf<p, TargetType, xs...>::type;


template <typename p, typename TargetType, template <typename...> class TypeListContainer, typename... xs>
struct ReplaceIf<p, TargetType, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<
                ReplaceIfT<p, TargetType, xs...>,
                TypeListContainer
          >
{ };


#endif //ROCKY_APP_REPLACEIF_H

