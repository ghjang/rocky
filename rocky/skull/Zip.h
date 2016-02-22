#ifndef ROCKY_SKULL_ZIP_H
#define ROCKY_SKULL_ZIP_H


#include "rocky/skull/ZipWith.h"


template <typename xs, typename ys>
struct Zip;

template <template <typename...> class TypeListContainer, typename... xs, typename... ys>
struct Zip<TypeListContainer<xs...>, TypeListContainer<ys...>>
{
private:
    struct AsPairTypeListContainerImpl
    {
        template <typename x, typename y>
        struct Apply : AsPairTypeListContainer<TypeListContainer, x, y>
        { };
    };

public:
    using type = typename ReplaceTypeListContainer<
                                typename ZipWith<
                                                AsPairTypeListContainerImpl,
                                                TypeList<xs...>,
                                                TypeList<ys...>
                                            >::type,
                                TypeListContainer
                            >::type;
};


template <typename xs, typename ys>
using ZipT = typename Zip<xs, ys>::type;


#endif //ROCKY_SKULL_ZIP_H

