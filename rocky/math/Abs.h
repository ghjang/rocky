#ifndef ROCKY_ABS_H
#define ROCKY_ABS_H


template <typename T>
constexpr auto Abs(T t)
{
    return (t < 0) ? -t : t;
}


#endif //ROCKY_ABS_H

