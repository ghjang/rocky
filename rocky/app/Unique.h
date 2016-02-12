#ifndef ROCKY_APP_UNIQUE_H
#define ROCKY_APP_UNIQUE_H


#include "rocky/skull/FoldL.h"
#include "rocky/skull/Elem.h"
#include "rocky/app/Find.h"


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
    using type = FoldLT<Quote<AppendTypeIfNotExist>, init_t, xs...>;
};


template <typename... xs>
using UniqueT = typename Unique<xs...>::type;


template <typename... xs>
struct Unique<TypeList<xs...>> : Unique<xs...>
{ };

template <typename x, typename y>
struct Unique<std::pair<x, y>> : Unique<x, y>
{ };

template <typename... xs>
struct Unique<std::tuple<xs...>> : TypeListToTuple<UniqueT<xs...>>
{ };


#endif //ROCKY_APP_UNIQUE_H

