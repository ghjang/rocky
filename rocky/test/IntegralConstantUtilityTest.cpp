#include "catch.hpp"

#include "rocky/meta/IntegralConstantUtility.h"


TEST_CASE("+ operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<5> + int_c<5> == int_c<10>, "5 + 5 = 10");
    static_assert(int_c<5> + int_c<5> == std::integral_constant<int, 10>{}, "5 + 5 = 10");
}

TEST_CASE("- operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<15> - int_c<5> == int_c<10>, "15 - 5 = 10");
    static_assert(int_c<15> - int_c<5> == std::integral_constant<int, 10>{}, "15 - 5 = 10");

    static_assert(int_c<15> - int_c<25> == int_c<-10>, "15 - 25 = -10");
    static_assert(int_c<15> - int_c<25> == std::integral_constant<int, -10>{}, "15 - 25 = -10");
}

TEST_CASE("* operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<5> * int_c<5> == int_c<25>, "5 * 5 = 25");
    static_assert(int_c<5> * int_c<5> == std::integral_constant<int, 25>{}, "5 * 5 = 25");

    static_assert(int_c<5> * int_c<-5> == int_c<-25>, "5 * -5 = -25");
}

TEST_CASE("/ operator overloading", "[IntegralConstantUtility]")
{
    static_assert(int_c<5> / int_c<5> == int_c<1>, "5 / 5 = 1");
    static_assert(int_c<5> / int_c<5> == std::integral_constant<int, 1>{}, "5 / 5 = 1");

    static_assert(int_c<5> / int_c<-5> == int_c<-1>, "5 / -5 = -1");

    static_assert(int_c<5> / int_c<2> == int_c<2>, "5 / 2 = 2");
}

TEST_CASE("user defined literal", "[IntegralConstantUtility]")
{
    static_assert(5_c + 5_c == 10_c, "5 + 5 = 10");
    static_assert(5_c + 5_c == std::integral_constant<int, 10>{}, "5 + 5 = 10");

    static_assert(50_c + 50_c == 100_c, "50 + 50 = 100");
    static_assert(50_c + 50_c == std::integral_constant<int, 100>{}, "50 + 50 = 100");

    static_assert(5_c + -5_c == 0_c, "5 + -5 = 0");
    static_assert(5_c + -5_c == std::integral_constant<int, 0>{}, "5 + -5 = 0");

    static_assert(5_c + -15_c == -10_c, "5 + -15 = -10");
    static_assert(5_c + -15_c == std::integral_constant<int, -10>{}, "5 + -15 = -10");

    static_assert(50_c + -150_c == -100_c, "50 + -150 = -100");
    static_assert(50_c + -150_c == std::integral_constant<int, -100>{}, "50 + -150 = -100");

    static_assert(50_c - 150_c == -100_c, "50 - 150 = -100");
    static_assert(50_c - 150_c == std::integral_constant<int, -100>{}, "50 - 150 = -100");
}

TEST_CASE("integral constant sum through class template IntegralConstantSum", "IntegralConstantUtility")
{
    using std::integral_constant;

    static_assert(
            IntegralConstantSum<integral_constant<int, 1>, integral_constant<int, 2>>() == 3,
            "integral constant sum: 1 + 2 = 3"
    );
}

TEST_CASE("integral constant multiplication through class template IntegralConstantMultiply", "IntegralConstantUtility")
{
    using std::integral_constant;

    static_assert(
            IntegralConstantMultiply<integral_constant<int, 2>, integral_constant<int, 3>>() == 6,
            "integral constant multiply: 2 * 3 = 6"
    );
}

TEST_CASE("type to bool integral constant", "[IntegralConstantUtility]")
{
    using std::is_same;
    using std::is_integral;
    using std::is_pointer;

    static_assert(
            is_same<one_t, TypeToBoolConstantType<is_integral>::template Convert<int>::type>(),
            "int should convert to one_t."
    );

    static_assert(
            is_same<zero_t, TypeToBoolConstantType<is_integral>::template Convert<double>::type>(),
            "double should convert to zero_t."
    );

    static_assert(
            is_same<one_t, TypeToBoolConstantType<is_pointer>::template Convert<int *>::type>(),
            "'int *' should convert to one_t."
    );

    static_assert(
            is_same<zero_t, TypeToBoolConstantType<is_pointer>::template Convert<int>::type>(),
            "int should convert to zero_t."
    );
}

