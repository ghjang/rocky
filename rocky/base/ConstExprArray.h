#ifndef ROCKY_CONSTEXPRARRAY_H
#define ROCKY_CONSTEXPRARRAY_H


#include <cstddef>


template <typename T, std::size_t N>
struct ConstExprArray
{
    constexpr std::size_t size() const
    { return N; }

    constexpr T const& operator [] (std::size_t i) const
    { return array_[i]; }

    constexpr T & operator [] (std::size_t i)
    { return array_[i]; }

    T array_[N]{};
};


#endif //ROCKY_CONSTEXPRARRAY_H

