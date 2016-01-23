#ifndef ROCKY_SKULL_FILTER_H
#define ROCKY_SKULL_FILTER_H


#include "rocky/meta/TypeListFlatten.h"
#include "rocky/meta/TypeSelection.h"
#include "rocky/skull/FoldL.h"


template <template <typename> class p, typename... xs>
struct Filter
{
private:
    using init_t = TypeList<>;

    template <typename lhs, typename rhs>
    struct AppendIfTrue : SelectTypeIf<
                                p<rhs>::value,
                                FlattenTypeList<lhs, rhs>,
                                lhs
                          >
    {
        static_assert(HasValueMember<p<rhs>>(), "Predicate p should have 'value' member.");
    };

public:
    using type = FoldLT<AppendIfTrue, init_t, xs...>;
};


template <template <typename> class p, typename... xs>
using FilterT = typename Filter<p, xs...>::type;


template <template <typename> class p, typename... xs>
struct Filter<p, TypeList<xs...>> : Filter<p, xs...>
{ };

template <template <typename> class p, typename... xs>
struct Filter<p, std::tuple<xs...>> : TypeListToTuple<FilterT<p, xs...>>
{ };


#endif //ROCKY_SKULL_FILTER_H

