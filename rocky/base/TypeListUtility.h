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

template <>
struct HasSameType<TypeList<>> : std::true_type
{ };

template <>
struct HasSameType<std::tuple<>> : std::true_type
{ };




#endif //ROCKY_BASE_TYPELISTUTILITY_H

