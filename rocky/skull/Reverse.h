#ifndef ROCKY_SKULL_REVERSE_H
#define ROCKY_SKULL_REVERSE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/skull/FoldR.h"


// THINK: Is it possible to introduce the underscore type place holder, '_', to simplify the codes below?

template <typename... xs>
struct Reverse
{
private:
    using init_t = TypeList<>;

    template <typename lhs, typename rhs>
    struct SwapImpl : FlattenAsTypeList<rhs, lhs>
    { };

public:
    using type = FoldRT<Quote<SwapImpl>, init_t, xs...>;
};


template <typename... xs>
using ReverseT = typename Reverse<xs...>::type;


template <typename... xs>
struct Reverse<TypeList<xs...>> : Reverse<xs...>
{ };

template <typename... xs>
struct Reverse<std::tuple<xs...>> : TypeListToTuple<ReverseT<xs...>>
{ };


#endif //ROCKY_SKULL_REVERSE_H

