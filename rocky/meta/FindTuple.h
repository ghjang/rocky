#ifndef ROCKY_TUPLESIZE_H
#define ROCKY_TUPLESIZE_H


#include "rocky/meta/TransformTuple.h"
#include "rocky/meta/ReverseTuple.h"


template <typename Tuple, typename TargetType>
struct FindElementType;

template <typename... list, typename TargetType>
struct FindElementType<std::tuple<list...>, TargetType>
{
private:
    template <typename T>
    struct IsSameAsTargetType
                : std::is_same<T, TargetType>
    { };

    using bool_result_t = typename TransformElementTypeToBoolConstantType<
                                        std::tuple<list...>,
                                        IsSameAsTargetType
                                    >::type;

    constexpr static auto boolResultArray_ = IntegralConstantElementTypeToArray<bool_result_t>;

    constexpr static auto FindFirstTrueValue()
    {
        int pos = -1;
        for (int i = 0; i < boolResultArray_.size(); ++i) {
            if (boolResultArray_[i]) {
                pos = i;
                break;
            }
        }
        return pos;
    }

public:
    constexpr static int value = FindFirstTrueValue();
};


template <typename Tuple, typename TargetType>
struct ReverseFindElementType;

template <typename... list, typename TargetType>
struct ReverseFindElementType<std::tuple<list...>, TargetType>
{
private:
    using reversed_tuple_t = typename ReverseElementType<std::tuple<list...>>::type;

    constexpr static auto targetTypeIndex_ = FindElementType<reversed_tuple_t, TargetType>::value;

public:
    constexpr static int value = (-1 == targetTypeIndex_) ? -1
                                                          : (sizeof...(list) - targetTypeIndex_ - 1);
};


#endif //ROCKY_TUPLESIZE_H

