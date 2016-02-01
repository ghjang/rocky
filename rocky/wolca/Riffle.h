#ifndef ROCKY_WOLCA_RIFFLE_H
#define ROCKY_WOLCA_RIFFLE_H


#include "rocky/skull/Replicate.h"
#include "rocky/skull/Zip.h"
#include "rocky/skull/FoldL.h"
#include "rocky/skull/Init.h"


template <typename T, typename... xs>
struct Riffle
{
private:
    template <typename lhs, typename rhs>
    struct FlattenImpl;

    template <typename... lhs, typename... rhs>
    struct FlattenImpl<TypeList<lhs...>, TypeList<rhs...>> : type_is<TypeList<lhs..., rhs...>>
    { };

    // NOTE: the last TypeList element of the zipped_t is unpacked by the FoldL specialization un-expectedly.
    // THINK: need to introduce some other type list container?
    template <typename... lhs, typename rhs>
    struct FlattenImpl<TypeList<lhs...>, rhs> : type_is<TypeList<lhs..., rhs>>
    { };

    // NOTE: zipped_t is TypeList of TypeLists.
    using zipped_t = ZipT<TL<xs...>, ReplicateT<sizeof...(xs), T>>;

    using flattened_t = FoldLT<FlattenImpl, TypeList<>, zipped_t>;

public:
    using type = InitT<flattened_t>;
};


template <typename T, typename... xs>
using RiffleT = typename Riffle<T, xs...>::type;


template <typename T>
struct Riffle<T> : type_is<TypeList<>>
{ };

template <typename T, typename... xs>
struct Riffle<T, TypeList<xs...>> : Riffle<T, xs...>
{ };

template <typename T, typename... xs>
struct Riffle<T, std::tuple<xs...>> : TypeListToTuple<RiffleT<T, xs...>>
{ };


#endif //ROCKY_WOLCA_RIFFLE_H

