#ifndef ROCKY_VARIANTUTILITY_H
#define ROCKY_VARIANTUTILITY_H


#include <type_traits>
#include <vector>

#include "boost/variant.hpp"

#include "rocky/meta/ForEachArgument.h"


template <typename T>
decltype(auto) MakeVariant(const T && arg)
{
    return boost::variant<T>(arg);
}


template <typename... Args>
decltype(auto) MakeVariantVector(const Args &&...  args)
{
    using element_t = boost::variant<std::decay_t<decltype(args)>...>;

    std::vector<element_t> v;
    v.reserve(sizeof...(args));

    ForEachArgument(
            [&v](const auto & e) { v.push_back(e); },
            args...
    );

    return v;
}


#endif //ROCKY_VARIANTUTILITY_H

