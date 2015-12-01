#ifndef ROCKY_UNIQUETUPLE_H
#define ROCKY_UNIQUETUPLE_H


#include "rocky/meta/Fold.h"
#include "rocky/meta/FindTuple.h"
#include "rocky/meta/TypeSelection.h"


template <typename Tuple>
struct UniqueElementType;

template <typename... list>
struct UniqueElementType<std::tuple<list...>>
{
private:
    using init_t = std::tuple<>;

    template <typename lhsType, typename rhsTuple>
    struct AppendTypeIfNotExist;

    template <typename lhsType, typename... rhsList>
    struct AppendTypeIfNotExist<lhsType, std::tuple<rhsList...>>
                : SelectTypeIf<
                        FindElementType<std::tuple<rhsList...>, lhsType>::value == -1,
                        std::tuple<lhsType, rhsList...>,
                        std::tuple<rhsList...>
                    >
    { };

public:
    using type = typename FoldRight<AppendTypeIfNotExist, init_t, list...>::type;
};


#endif //ROCKY_UNIQUETUPLE_H

