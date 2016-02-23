#ifndef ROCKY_SKULL_REVERSE_H
#define ROCKY_SKULL_REVERSE_H


#include "rocky/base/TypeListFlatten.h"
#include "rocky/base/Swap.h"
#include "rocky/skull/FoldR.h"


template <typename... xs>
struct Reverse
        : FoldR<
                Compose<
                        Quote<FlattenTypeListWithUnpack>,
                        Quote<Swap>
                >,
                TypeList<>, // init
                xs...
          >
{ };


template <typename... xs>
using ReverseT = typename Reverse<xs...>::type;


template <template <typename...> class TypeListContainer, typename... xs>
struct Reverse<TypeListContainer<xs...>>
        : ReplaceTypeListContainer<ReverseT<xs...>, TypeListContainer>
{ };


#endif //ROCKY_SKULL_REVERSE_H

