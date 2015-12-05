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

    template <typename lhsTuple, typename rhsType>
    struct AppendTypeIfNotExist;

    template <typename... lhsList, typename rhsType>
    struct AppendTypeIfNotExist<std::tuple<lhsList...>, rhsType>
                : SelectTypeIf<
                        FindElementType<std::tuple<lhsList...>, rhsType>::value == -1,
                        std::tuple<lhsList..., rhsType>,
                        std::tuple<lhsList...>
                    >
    { };

public:
    using type = typename FoldLeft<AppendTypeIfNotExist, init_t, list...>::type;
};


template <typename... T>
struct MakeUniqueElementTypeTuple
            : UniqueElementType<std::tuple<T...>>
{ };


#endif //ROCKY_UNIQUETUPLE_H

