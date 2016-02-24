#ifndef ROCKY_WOLCA_FLATTEN_H
#define ROCKY_WOLCA_FLATTEN_H


#include "rocky/skull/FoldL.h"


template <typename... xs>
struct Flatten;

template <typename... xs>
using FlattenT = typename Flatten<xs...>::type;

template <typename... xs>
struct Flatten
{
private:
    template <typename lhs, typename rhs>
    struct FlattenImpl
            : FlattenTypeList<lhs, FlattenT<rhs>>
    { };

public:
    using type = FoldLT<
                    Quote<FlattenImpl>,
                    TypeList<>, // init
                    xs...
                 >;
};

template <typename x>
struct Flatten<x> : type_is<TypeList<x>>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Flatten<TypeListContainer<xs...>> : Flatten<xs...>
{ };


#endif //ROCKY_WOLCA_FLATTEN_H

