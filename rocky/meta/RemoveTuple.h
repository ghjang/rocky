#ifndef ROCKY_REMOVETUPLE_H
#define ROCKY_REMOVETUPLE_H


#include "rocky/meta/TransformTuple.h"


template <typename Tuple, template <typename> class Predicate>
struct RemoveElementType;

template <typename... list, template <typename> class Predicate>
struct RemoveElementType<std::tuple<list...>, Predicate>
{
private:
    using bool_result_t = typename TransformElementTypeToBoolConstantType<std::tuple<list...>, Predicate>::type;
    using bool_seq_t = typename ConvertToIntegerSequenceType<bool_result_t>::type;
    using inverted_bool_seq_t = typename InvertBoolSequence<bool_seq_t>::type;
    using target_element_index_seq_t = typename ConvertBoolSequenceToTrueValueIndexSequence<inverted_bool_seq_t >::type;

public:
    using type = typename ExtractElementType<std::tuple<list...>, target_element_index_seq_t>::type;
};


#endif //ROCKY_REMOVETUPLE_H

