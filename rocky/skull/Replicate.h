#ifndef ROCKY_SKULL_REPLICATE_H
#define ROCKY_SKULL_REPLICATE_H


#include "rocky/skull/Head.h"


template <std::size_t n, typename x>
struct Replicate
{
private:
    template <typename IndexSequence, typename T>
    struct ReplicateImpl;

    template <std::size_t... i, typename T>
    struct ReplicateImpl<std::index_sequence<i...>, T>
            : type_is<
                    TypeList<
                            HeadT<TypeList<T, std::integral_constant<std::size_t, i>>>...
                    >
              >
    { };

public:
    using type = typename ReplicateImpl<std::make_index_sequence<n>, x>::type;
};


template <std::size_t n, typename x>
using ReplicateT = typename Replicate<n, x>::type;


template <typename x>
struct Replicate<0, x> : type_is<TypeList<>>
{ };


#endif //ROCKY_SKULL_REPLICATE_H

