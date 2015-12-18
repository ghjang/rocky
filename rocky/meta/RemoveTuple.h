#ifndef ROCKY_REMOVETUPLE_H
#define ROCKY_REMOVETUPLE_H


#include "rocky/meta/TransformTuple.h"


template <template <typename> class Predicate, typename Tuple>
struct RemoveElementType;

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


#endif //ROCKY_REMOVETUPLE_H

