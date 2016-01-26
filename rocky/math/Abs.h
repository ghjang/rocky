#ifndef ROCKY_BASE_ABS_H
#define ROCKY_BASE_ABS_H


#include <type_traits>


namespace Detail
{
    template<typename T>
    inline constexpr auto AbsImpl(T t, std::true_type)
    {
        return (t < 0) ? -t : t;
    }

    template<typename T>
    inline constexpr auto AbsImpl(T t, std::false_type)
    {
        return t;
    }
} // namespace Detail


template
<
        typename T,
        typename = std::enable_if_t<std::is_arithmetic<T>::value>
>
constexpr auto Abs(T t)
{
    return Detail::AbsImpl(t, std::is_signed<T>());
}


#endif //ROCKY_BASE_ABS_H

