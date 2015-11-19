#ifndef ROCKY_FOREACHARGUMENT_H
#define ROCKY_FOREACHARGUMENT_H


#include <initializer_list>
#include <utility>


template <typename F, typename... Args>
decltype(auto) ForEachArgument(F && f, Args &&... args)
{
    (void) std::initializer_list<int> { (f(std::forward<Args>(args)), 0)... };
    return std::move(f);
}


#endif //ROCKY_FOREACHARGUMENT_H

