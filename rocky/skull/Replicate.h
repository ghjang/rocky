#ifndef ROCKY_SKULL_REPLICATE_H
#define ROCKY_SKULL_REPLICATE_H


#include "rocky/skull/Head.h"


template <typename n, typename x>
struct Replicate;

template <typename T, T n, typename x>
struct Replicate<std::integral_constant<T, n>, x>
{
private:
    template <typename IndexSequence, typename T1>
    struct ReplicateImpl;

    template <std::size_t... i, typename T1>
    struct ReplicateImpl<std::index_sequence<i...>, T1>
            : type_is<
                    TypeList<
                            HeadT<TypeList<T1, std::integral_constant<std::size_t, i>>>...
                    >
              >
    { };

public:
    using type = typename ReplicateImpl<std::make_index_sequence<n>, x>::type;
};

template <typename x>
struct Replicate<std::integral_constant<std::size_t, 0>, x> : type_is<TypeList<>>
{ };


template <std::size_t n, typename x>
using ReplicateT = typename Replicate<std::integral_constant<std::size_t, n>, x>::type;


#endif //ROCKY_SKULL_REPLICATE_H

