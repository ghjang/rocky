#ifndef ROCKY_APP_REMOVE_H
#define ROCKY_APP_REMOVE_H


#include "rocky/base/TypeUtility.h"
#include "rocky/skull/Filter.h"


/**
 * @tparam p predicate metafunction class
 */
template <typename p, typename... xs>
using RemoveIf = Filter<NegatePredicate<p>, xs...>;

template <typename p, typename... xs>
using RemoveIfT = typename RemoveIf<p, xs...>::type;


/**
 * NOTE: Following implementation doesn't compile anymore.
 *          By the way, the usage example of 'Transform' is still useful for reference.
 */
/*
template <template <typename> class Predicate, typename... list>
struct RemoveElementType<Predicate, std::tuple<list...>>
{
private:
    using bool_result_t = typename TransformElementTypeToBoolConstantType<Predicate, std::tuple<list...>>::type;
    using bool_seq_t = typename ConvertToIntegerSequenceType<bool_result_t>::type;
    using inverted_bool_seq_t = typename InvertBoolSequence<bool_seq_t>::type;
    using target_element_index_seq_t = typename ConvertBoolSequenceToTrueValueIndexSequence<inverted_bool_seq_t >::type;

public:
    using type = typename ExtractElementType<target_element_index_seq_t, std::tuple<list...>>::type;
};
*/


#endif //ROCKY_APP_REMOVE_H

