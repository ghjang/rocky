#include "catch.hpp"

#include "rocky/meta/TransformTuple.h"

#include <type_traits>
#include <memory>


namespace
{
    template <typename T>
    struct AddSharedPtr
    {
        using type = std::shared_ptr<T>;
    };

    template <typename T>
    struct AddSharedPtrIfIntegral
                : SelectTypeIf<
                        std::integral_constant<bool, std::is_integral<T>::value>,
                        std::shared_ptr<T>,
                        T
                    >
    { };


    template <typename T>
    struct IntegralTypeToOne
            : SelectTypeIf<
                    std::integral_constant<bool, std::is_integral<T>::value>,
                    std::true_type,
                    std::false_type
                >
    { };
}


TEST_CASE("transforming tuple elements", "[TransformTuple]")
{
    using std::tuple;
    using std::make_tuple;

    auto const originalTupleObj = make_tuple('a', 2, 3.0);
    auto const transformedTupleObj = TransformElement(originalTupleObj, [](auto arg) { return arg * 2; });
    REQUIRE(transformedTupleObj == make_tuple('a' * 2, 2 * 2, 3.0 * 2));
}

TEST_CASE("transforming tuple element types to pointer types", "[TransformTuple]")
{
    using std::is_same;
    using std::add_pointer;
    using std::tuple;

    using tuple_t = tuple<char, int, double>;
    using ptr_tuple_t = tuple<char *, int *, double *>;
    static_assert(
            is_same<ptr_tuple_t, typename TransformElementType<tuple_t, add_pointer>::type>(),
            "transformed tuple_t should be ptr_tuple_t."
    );
}

TEST_CASE("transforming tuple element types to shard_ptr types", "[TransformTuple]")
{
    using std::is_same;
    using std::shared_ptr;
    using std::tuple;

    using tuple_t = tuple<char, int, double>;
    using shared_ptr_tuple_t = tuple<shared_ptr<char>, shared_ptr<int>, shared_ptr<double>>;
    static_assert(
            is_same<shared_ptr_tuple_t, typename TransformElementType<tuple_t, AddSharedPtr>::type>(),
            "transformed tuple_t shouble be shared_ptr_tuple_t."
    );
}

TEST_CASE("transforming tuple integral element types to shard_ptr types", "[TransformTuple]")
{
    using std::is_same;
    using std::shared_ptr;
    using std::tuple;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using integral_ptr_tuple_t = tuple<shared_ptr<char>, shared_ptr<int>, double, shared_ptr<uint64_t>, float>;
    static_assert(
            is_same<integral_ptr_tuple_t, typename TransformElementType<tuple_t, AddSharedPtrIfIntegral>::type>(),
            "transformed tuple_t should be integral_ptr_tuple_t."
    );
}

TEST_CASE("transforming tuple integral element types to integral value true_type or false_type", "[TransformTuple]")
{
    using std::is_same;
    using std::tuple;
    using std::true_type;
    using std::false_type;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using integral_tuple_t = tuple<true_type, true_type, false_type, true_type, false_type>;
    static_assert(
            is_same<
                integral_tuple_t,
                typename TransformElementType<
                                tuple_t,
                                IntegralTypeToOne   // should have 'type' member.
                            >::type
            >(),
            "transformed tuple_t should be integral_tuple_t."
    );
}

TEST_CASE("transforming tuple integral element types to integral value true_type or false_type"
          "by using TransformElementTypeToBoolConstantType",
          "[TransformTuple]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;
    using std::true_type;
    using std::false_type;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using integral_tuple_t = tuple<true_type, true_type, false_type, true_type, false_type>;
    static_assert(
            is_same<
                integral_tuple_t,
                typename TransformElementTypeToBoolConstantType<
                                tuple_t,
                                is_integral // should have 'value' member.
                            >::type
            >(),
            "transformed tuple_t should be integral_tuple_t."
    );
}

TEST_CASE("integral constant element type to array", "[TransformTuple]")
{
    using std::tuple;
    using std::tuple_size;
    using std::true_type;
    using std::false_type;

    using tuple_t = tuple<true_type, true_type, false_type, true_type, false_type>;
    auto arr = IntegralConstantElementTypeToArray<tuple_t>;
    REQUIRE(arr.size() == tuple_size<tuple_t>());
    REQUIRE(tuple_size<tuple_t>() == 5);
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 1);
    REQUIRE(arr[2] == 0);
    REQUIRE(arr[3] == 1);
    REQUIRE(arr[4] == 0);
}

TEST_CASE("integral constant element type to integer sequence", "[TransformTuple]")
{
    using std::is_same;
    using std::tuple;
    using std::integer_sequence;
    using std::true_type;
    using std::false_type;

    using tuple_t = tuple<true_type, true_type, false_type, true_type, false_type>;
    using sequence_t = integer_sequence<int, 1, 1, 0, 1, 0>;

    static_assert(
            is_same<sequence_t, typename ConvertToIntegerSequenceType<tuple_t>::type>(),
            "transformed tuple_t should be same as sequence_t."
    );
}

TEST_CASE("integral constant element type to integer sequence with type alias int_c_t", "[TransformTuple]")
{
    using std::is_same;
    using std::tuple;
    using std::integer_sequence;

    using tuple_t = tuple<int_c_t<1>, int_c_t<2>, int_c_t<0>, int_c_t<100>, int_c_t<123>>;
    using sequence_t = integer_sequence<int, 1, 2, 0, 100, 123>;

    static_assert(
            is_same<sequence_t, typename ConvertToIntegerSequenceType<tuple_t>::type>(),
            "transformed tuple_t should be same as sequence_t."
    );
}

TEST_CASE("bool value sequence to true value index sequence", "[TransformTuple]")
{
    using std::is_same;
    using std::integer_sequence;
    using std::true_type;
    using std::false_type;

    {
        using bool_t = integer_sequence<int, 0, 0, 0, 0, 0>;
        using sequence_t = integer_sequence<int>;

        static_assert(
                is_same<sequence_t, typename TransformBoolSequenceToTrueValueIndexSequence<bool_t>::type>(),
                "transformed bool_t should be same as sequence_t."
        );
    }

    {
        using bool_t = integer_sequence<int, 1, 0, 0, 0, 0>;
        using sequence_t = integer_sequence<int, 0>;

        static_assert(
                is_same<sequence_t, typename TransformBoolSequenceToTrueValueIndexSequence<bool_t>::type>(),
                "transformed bool_t should be same as sequence_t."
        );
    }

    {
        using bool_t = integer_sequence<int, 0, 0, 0, 0, 1>;
        using sequence_t = integer_sequence<int, 4>;

        static_assert(
                is_same<sequence_t, typename TransformBoolSequenceToTrueValueIndexSequence<bool_t>::type>(),
                "transformed bool_t should be same as sequence_t."
        );
    }

    {
        using bool_t = integer_sequence<int, 1, 1, 0, 1, 0>;
        using sequence_t = integer_sequence<int, 0, 1, 3>;

        static_assert(
                is_same<sequence_t, typename TransformBoolSequenceToTrueValueIndexSequence<bool_t>::type>(),
                "transformed bool_t should be same as sequence_t."
        );
    }
}

TEST_CASE("bool value sequence inversion", "[TransformTuple]")
{
    using std::is_same;
    using std::integer_sequence;

    using bool_t = integer_sequence<int, 1, 1, 0, 1, 0>;
    using inverted_bool_t = integer_sequence<int, 0, 0, 1, 0, 1>;
    static_assert(
            is_same<inverted_bool_t, typename InvertBoolSequenceType<bool_t>::type>(),
            "inverted bool_t should be same as inverted_bool_t."
    );
}

