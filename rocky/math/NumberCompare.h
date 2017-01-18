#ifndef ROCKY_MATH_NUMBER_COMPARE_H
#define ROCKY_MATH_NUMBER_COMPARE_H


#include <limits>
#include <type_traits>


// refer to the following for floating point number comparison:
//      http://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
//      http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
template
<
    typename T, typename U,
    typename = std::enable_if_t<std::is_floating_point<std::common_type_t<T, U>>::value>
>
bool is_almost_equal(T a, U b, int ulp = 1)
{
    using diff_t = decltype(a - b);
    return std::fabs(a - b) < std::numeric_limits<diff_t>::epsilon() * ulp;
}

template
<
    typename T, typename U,
    typename dummy = void,
    typename = std::enable_if_t<std::is_integral<std::common_type_t<T, U>>::value>
>
bool is_almost_equal(T a, U b)
{
    return a == b;
}


#endif // ROCKY_MATH_NUMBER_COMPARE_H
