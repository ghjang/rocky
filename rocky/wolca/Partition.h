#ifndef ROCKY_WOLCA_PARTITION_H
#define ROCKY_WOLCA_PARTITION_H


#include "rocky/skull/Take.h"
#include "rocky/skull/Drop.h"


namespace Detail
{
    template <typename T, typename... xs>
    struct PartitionImpl;

    template <typename T, T n, typename... rs, typename... xs>
    struct PartitionImpl<std::integral_constant<T, n>, TypeList<rs...>, TypeList<xs...>>
            : SelectTypeIf<
                    (n > sizeof...(xs)),
                    TypeList<rs...>,
                    PartitionImpl<
                            std::integral_constant<T, n>,
                            TypeList<rs..., TakeT<n, xs...>>,
                            DropT<n, xs...>
                    >
              >
    { };
} // namespace Detail


template <typename n, typename... xs>
struct Partition;


template <typename n, typename... xs>
using PartitionT = typename Partition<n, xs...>::type;


template <typename T, T n, typename... xs>
struct Partition<std::integral_constant<T, n>, xs...>
{
    static_assert(n > 0, "n should be greater than zero.");
    static_assert(
            std::is_integral<decltype(sizeof...(xs) / n)>(),
            "the type of number of partition should be integral."
    );

    using type = SelectTypeIfT<
                    (n > sizeof...(xs)),
                    TypeList<>,
                    Detail::PartitionImpl<std::integral_constant<T, n>, TypeList<TakeT<n, xs...>>, DropT<n, xs...>>
                 >;
};


template <typename... xs>
using ListToPairT = PartitionT<std::integral_constant<int, 2>, xs...>;


#endif //ROCKY_WOLCA_PARTITION_H

