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
    using init_t = TypeList<>;

    template <typename lhs, typename rhs>
    struct AppendIfTrue : SelectTypeIf<
                                ApplyT<p, rhs>::value,
                                FlattenAsTypeList<lhs, rhs>,
                                lhs
                          >
    {
        static_assert(HasValueMember<ApplyT<p, rhs>>(), "applied predicate p should have 'value' member.");
    };

public:
    using type = FoldLT<AppendIfTrue, init_t, xs...>;
};


template <typename p, typename... xs>
using FilterT = typename Filter<p, xs...>::type;


template <typename p, typename... xs>
struct Filter<p, TypeList<xs...>> : Filter<p, xs...>
{ };

template <typename p, typename... xs>
struct Filter<p, std::tuple<xs...>> : TypeListToTuple<FilterT<p, xs...>>
{ };


#endif //ROCKY_SKULL_FILTER_H

