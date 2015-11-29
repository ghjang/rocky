#include "catch.hpp"

#include "rocky/meta/TransformTuple.h"

#include <type_traits>
#include <memory>

#include "rocky/meta/TypeSelection.h"


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
                    one_t,
                    zero_t
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

TEST_CASE("transforming tuple integral element types to integral value 1", "[TransformTuple]")
{
    using std::is_same;
    using std::tuple;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using integral_tuple_t = tuple<one_t, one_t, zero_t, one_t, zero_t>;
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

TEST_CASE("transforming tuple integral element types to integral value 1"
          "by using TransformElementTypeToBoolConstantType",
          "[TransformTuple]")
{
    using std::is_same;
    using std::is_integral;
    using std::tuple;

    using tuple_t = tuple<char, int, double, uint64_t, float>;
    using integral_tuple_t = tuple<one_t, one_t, zero_t, one_t, zero_t>;
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

TEST_CASE("integral constant element type to bool array", "[TransformTuple]")
{
    using std::tuple;
    using std::tuple_size;

    using tuple_t = tuple<one_t, one_t, zero_t, one_t, zero_t>;
    auto arr = IntegralConstantElementTypeToBoolArray<tuple_t>;
    REQUIRE(arr.size() == tuple_size<tuple_t>());
    REQUIRE(tuple_size<tuple_t>() == 5);
    REQUIRE(arr[0] == 1);
    REQUIRE(arr[1] == 1);
    REQUIRE(arr[2] == 0);
    REQUIRE(arr[3] == 1);
    REQUIRE(arr[4] == 0);
}

TEST_CASE("integral constant element type to sequence", "[TransformTuple]")
{
    using std::is_same;
    using std::tuple;
    using std::index_sequence;

    using tuple_t = tuple<one_t, one_t, zero_t, one_t, zero_t>;
    using sequence_t = index_sequence<1, 1, 0, 1, 0>;

    static_assert(is_same<sequence_t, typename TransformToSequenceType<tuple_t>::type>(), "");
}

