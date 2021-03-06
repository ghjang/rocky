#ifndef ROCKY_BASE_FOREACHARGUMENT_H
#define ROCKY_BASE_FOREACHARGUMENT_H


#include <initializer_list>
#include <utility>


template <typename F, typename... Args>
decltype(auto) ForEachArgument(F && f, Args &&... args)
{
    (void) std::initializer_list<int> { (f(std::forward<Args>(args)), 0)... };
    return std::forward<F>(f);
}


#endif //ROCKY_BASE_FOREACHARGUMENT_H

