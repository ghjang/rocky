#ifndef ROCKY_MATH_NUMBER_SEQUENCE2_H
#define ROCKY_MATH_NUMBER_SEQUENCE2_H


#include "rocky/math/NumberSequence.h"
#include "rocky/et/ReplaceOpTag.h"


struct bitwise_xor_t;
struct pow_t;

template <typename T>
struct TD;

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    template <typename> class Operation,
    template <typename, typename, bool, bool> class Storage,
    typename T = int, typename U = T, typename V = std::common_type_t<T, U>
>
auto number_seq2(expression<Left, OpTag, Right, IsLeftRValRef, IsRightRValRef, Operation, Storage> && expr,
                 T init = 0, U increment = 1, V max = std::numeric_limits<V>::max())
{
    using expr_t = ReplaceOpTagT<std::decay_t<decltype(expr)>, bitwise_xor_t, pow_t>;
    return number_seq(expr_t{ std::move(expr) }, init, increment, max);
}


#endif // ROCKY_MATH_NUMBER_SEQUENCE2_H
