#ifndef ROCKY_WOLCA_FLATTEN_H
#define ROCKY_WOLCA_FLATTEN_H


#include "rocky/skull/FoldL.h"


namespace Detail
{
    template <typename... xs>
    struct FlattenImpl;

    template <typename... xs>
    using FlattenImplT = typename FlattenImpl<xs...>::type;

    template <typename... xs>
    struct FlattenImpl
    {
    private:
        template <typename lhs, typename rhs>
        struct Flattener : FlattenTypeList<lhs, FlattenImplT<rhs>>
        { };

    public:
        using type = FoldLT<
                        Quote<Flattener>,
                        TypeList<>, // init
                        xs...
                     >;
    };

    template <typename x>
    struct FlattenImpl<x> : type_is<TypeList<x>>
    { };

    template <template <typename...> class TypeListContainer, typename... xs>
    struct FlattenImpl<TypeListContainer<xs...>> : FlattenImpl<xs...>
    { };
} // namespace Detail


template <typename... xs>
struct Flatten : Detail::FlattenImpl<xs...>
{ };

template <typename... xs>
using FlattenT = typename Flatten<xs...>::type;

template <template <typename...> class TypeListContainer, typename... xs>
struct Flatten<TypeListContainer<xs...>>
        : ReplaceTypeListContainer<FlattenT<xs...>, TypeListContainer>
{ };


#endif //ROCKY_WOLCA_FLATTEN_H

