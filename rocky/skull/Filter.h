#ifndef ROCKY_SKULL_FILTER_H
#define ROCKY_SKULL_FILTER_H


#include "rocky/base/TypeUtility.h"
#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/TypeSelection.h"
#include "rocky/skull/FoldL.h"


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename... xs>
struct Filter
{
private:
    struct AppendIfTrue
    {
        template <typename lhs, typename rhs>
        struct Apply
                : SelectTypeIf<
                        ApplyT<p, rhs>::value,
                        FlattenTypeList<lhs, rhs>,
                        lhs
                  >
        {
            static_assert(HasValueMember<ApplyT<p, rhs>>(), "applied predicate p should have 'value' member.");
        };
    };

public:
    using type = FoldLT<
                    AppendIfTrue,
                    TypeList<>, // init
                    xs...
                 >;
};


template <typename p, typename... xs>
using FilterT = typename Filter<p, xs...>::type;


template <typename p, template <typename...> class TypeListContainer, typename... xs>
struct Filter<p, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<FilterT<p, xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_FILTER_H

