#ifndef ROCKY_WOLCA_RIFFLE_H
#define ROCKY_WOLCA_RIFFLE_H


#include "rocky/skull/Init.h"
#include "rocky/skull/FoldL.h"
#include "rocky/skull/Zip.h"
#include "rocky/skull/Replicate.h"


template <typename T, typename... xs>
struct Riffle
        : Apply<
                Compose<
                        Quote<Init>,
                        BindFirst<Quote<FoldL>, Quote<FlattenTypeList>, TypeList<>>,
                        Quote<Zip>
                >,
                TL<xs...>, ReplicateT<sizeof...(xs), T>
          >
{ };


template <typename T, typename... xs>
using RiffleT = typename Riffle<T, xs...>::type;


template <typename T>
struct Riffle<T> : type_is<TypeList<>>
{ };

template <typename T, template <typename...> class TypeListContainer, typename... xs>
struct Riffle<T, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<RiffleT<T, xs...>, TypeListContainer>
{ };


#endif //ROCKY_WOLCA_RIFFLE_H

