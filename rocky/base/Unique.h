#ifndef ROCKY_UNIQUE_H
#define ROCKY_UNIQUE_H


#include "rocky/meta/Find.h"
#include "rocky/skull/FoldL.h"
#include "rocky/skull/Elem.h"


template <typename... xs>
struct Unique;

template <typename... xs>
struct Unique
{
private:
    using init_t = TypeList<>;

    template <typename lhs, typename rhs>
    struct AppendTypeIfNotExist;

    template <typename... lhs, typename rhs>
    struct AppendTypeIfNotExist<TypeList<lhs...>, rhs>
                : std::conditional<
                        !Elem<rhs, lhs...>(),
                        TypeList<lhs..., rhs>,
                        TypeList<lhs...>
                    >
    { };

public:
    using type = FoldLT<AppendTypeIfNotExist, init_t, xs...>;
};


template <typename... xs>
using UniqueT = typename Unique<xs...>::type;


template <typename... xs>
struct Unique<TypeList<xs...>> : Unique<xs...>
{ };

template <typename... xs>
struct Unique<std::tuple<xs...>> : TypeListToTuple<UniqueT<xs...>>
{ };


#endif //ROCKY_UNIQUE_H

