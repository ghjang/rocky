#ifndef ROCKY_VARIANTUTILITY_H
#define ROCKY_VARIANTUTILITY_H


#include <type_traits>
#include <vector>

#include "boost/variant.hpp"

#include "rocky/meta/ForEachArgument.h"
#include "rocky/meta/UniqueTuple.h"


template <typename Tuple>
struct TupleToVariant;

template <typename... list>
struct TupleToVariant<std::tuple<list...>>
{
    using type = boost::variant<list...>;
};


template <typename T>
decltype(auto) MakeVariant(const T && arg)
{
    return boost::variant<T>(arg);
}


template <typename... Args>
decltype(auto) MakeVariantVector(const Args &&...  args)
{
    using unique_tuple_t = typename MakeUniqueElementTypeTuple<std::decay_t<decltype(args)>...>::type;
    using element_t = typename TupleToVariant<unique_tuple_t>::type;

    std::vector<element_t> v;
    v.reserve(sizeof...(args));

    ForEachArgument(
            [&v](const auto & e) { v.push_back(e); },
            args...
    );

    return v;
}


#endif //ROCKY_VARIANTUTILITY_H

