#ifndef ROCKY_SKULL_CONCAT_H
#define ROCKY_SKULL_CONCAT_H


#include "rocky/skull/FoldL.h"


template <typename xs, typename... xss>
struct Concat
{
private:
    template <typename lhs, typename rhs>
    struct ConcatImpl;

    template <typename... lhsXs, typename... rhsYs>
    struct ConcatImpl<TypeList<lhsXs...>, TypeList<rhsYs...>> : type_is<TypeList<lhsXs..., rhsYs...>>
    { };

    template <typename... lhsXs, typename... rhsYs>
    struct ConcatImpl<std::tuple<lhsXs...>, std::tuple<rhsYs...>> : type_is<std::tuple<lhsXs..., rhsYs...>>
    { };

public:
    using type = FoldLT<Quote<ConcatImpl>, xs, xss...>;
};


template <typename... xss>
using ConcatT = typename Concat<xss...>::type;


#endif //ROCKY_SKULL_CONCAT_H

