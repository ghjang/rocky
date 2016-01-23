#ifndef ROCKY_UNIQUETUPLE_H
#define ROCKY_UNIQUETUPLE_H


#include "rocky/meta/FindTuple.h"
#include "rocky/skull/FoldL.h"


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
                : std::conditional<
                        !IsOneOf<rhsType, lhsList...>::value,
                        std::tuple<lhsList..., rhsType>,
                        std::tuple<lhsList...>
                    >
    { };

public:
    using type = FoldLT<AppendTypeIfNotExist, init_t, list...>;
};


template <typename... list>
struct MakeUniqueElementTypeTuple
            : UniqueElementType<std::tuple<list...>>
{ };


#endif //ROCKY_UNIQUETUPLE_H

