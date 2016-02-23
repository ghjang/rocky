#ifndef ROCKY_BASE_TYPELISTUTILITY_H
#define ROCKY_BASE_TYPELISTUTILITY_H


#include "rocky/skull/Length.h"
#include "rocky/app/Unique.h"


template <typename... xs>
struct HasSameType
        : std::conditional_t<
                Length<UniqueT<xs...>>() == 1,
                std::true_type,
                std::false_type
          >
{ };

template <>
struct HasSameType<> : std::true_type
{ };

template <template <typename...> class TypeListContainer>
struct HasSameType<TypeListContainer<>> : std::true_type
{ };


template <typename xs>
struct EmptyTypeListContainerOf;

template <template <typename...> class TypeListContainer, typename... xs>
struct EmptyTypeListContainerOf<TypeListContainer<xs...>> : type_is<TypeListContainer<>>
{ };

template <typename xs>
using EmptyTypeListContainerOfT = typename EmptyTypeListContainerOf<xs>::type;


#endif //ROCKY_BASE_TYPELISTUTILITY_H

