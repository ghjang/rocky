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

    template <typename... lhs, typename a, typename b>
    struct FlattenImpl<TypeList<lhs...>, TypeList<a, b>> : type_is<TypeList<lhs..., a, b>>
    { };

    // NOTE: zipped_t is TypeList of TypeLists of which length is two.
    using zipped_t = ZipT<TL<xs...>, ReplicateT<sizeof...(xs), T>>;

    using flattened_t = FoldLWithUnpackT<Quote<FlattenImpl>, TypeList<>, zipped_t>;

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
struct Riffle<T, std::tuple<xs...>> : ToTuple<RiffleT<T, xs...>>
{ };


#endif //ROCKY_WOLCA_RIFFLE_H

