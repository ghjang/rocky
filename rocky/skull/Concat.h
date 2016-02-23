#ifndef ROCKY_SKULL_CONCAT_H
#define ROCKY_SKULL_CONCAT_H


#include "rocky/base/TypeListUtility.h"
#include "rocky/skull/FoldL.h"


template <typename xs, typename... xss>
struct Concat
{
private:
    template <typename lhs, typename rhs>
    struct ConcatImpl;

    template <template <typename...> class TypeListContainer, typename... lhsXs, typename... rhsYs>
    struct ConcatImpl<TypeListContainer<lhsXs...>, TypeListContainer<rhsYs...>>
            : type_is<TypeListContainer<lhsXs..., rhsYs...>>
    { };

public:
    using type = FoldLT<
                    Quote<ConcatImpl>,
                    EmptyTypeListContainerOfT<xs>,
                    EmptyTypeListContainerOfT<xs>,
                    xs,
                    xss...
                 >;
};


template <typename... xss>
using ConcatT = typename Concat<xss...>::type;


#endif //ROCKY_SKULL_CONCAT_H

