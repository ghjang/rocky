#ifndef ROCKY_REMOVETUPLE_H
#define ROCKY_REMOVETUPLE_H


#include "rocky/meta/TypeUtility.h"
#include "rocky/meta/Fold.h"

//#include "rocky/meta/TransformTuple.h"


template <template <typename> class Predicate, typename Tuple>
struct RemoveElementType;

template <template <typename> class Predicate, typename... list>
struct RemoveElementType<Predicate, std::tuple<list...>>
{
private:
    static_assert(HasValueMember<Predicate<int>>(), "Predicate should have 'value' member.");

    using init_t = std::tuple<>;

    template <typename lhsTuple, typename rhsType>
    struct AppendTypeIf;

    template <typename... lhsList, typename rhsType>
    struct AppendTypeIf<std::tuple<lhsList...>, rhsType>
            : std::conditional<
                    Predicate<rhsType>::value,
                    std::tuple<lhsList...>,
                    std::tuple<lhsList..., rhsType>
            >
    { };

public:
    using type = typename FoldLeft<AppendTypeIf, init_t, list...>::type;
};


/**
 * NOTE: Following implementation also works. But, it's more complicated.
 *          The usage example of 'Transform' is still useful for reference.
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


#endif //ROCKY_REMOVETUPLE_H

