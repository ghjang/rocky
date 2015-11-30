#ifndef ROCKY_REMOVETUPLE_H
#define ROCKY_REMOVETUPLE_H


#include <tuple>

#include "rocky/meta/TransformTuple.h"


template <typename Tuple, template <typename> class Predicate>
struct RemoveElementType;

template <typename... list, template <typename> class Predicate>
struct RemoveElementType<std::tuple<list...>, Predicate>
{
private:
    using bool_result_t = typename TransformElementTypeToBoolConstantType<std::tuple<list...>, Predicate>::type;
    using bool_seq_t = typename TransformToIntegerSequenceType<bool_result_t>::type;
    using inverted_bool_seq_t = typename InvertBoolSequenceType<bool_seq_t>::type;
    using target_element_index_seq_t = typename TransformBoolSequenceToTrueValueIndexSequence<
                                                        inverted_bool_seq_t
                                                >::type;

    template <typename IndexSequence>
    struct ExtractElementTypeImpl;

    template <typename T, T... i>
    struct ExtractElementTypeImpl<std::integer_sequence<T, i...>>
    {
        using type = std::tuple<std::tuple_element_t<i, std::tuple<list...>>...>;
    };

public:
    using type = typename ExtractElementTypeImpl<target_element_index_seq_t>::type;
};


#endif //ROCKY_REMOVETUPLE_H

