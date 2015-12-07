#ifndef ROCKY_VARIANTUTILITY_H
#define ROCKY_VARIANTUTILITY_H


#include <type_traits>
#include <string>
#include <vector>

#include "boost/variant.hpp"

#include "rocky/meta/TypeUtility.h"
#include "rocky/meta/ForEachArgument.h"
#include "rocky/meta/UniqueTuple.h"


template <typename Tuple>
struct TupleTypeToVariantType;

template <typename... list>
struct TupleTypeToVariantType<std::tuple<list...>>
{
    using type = boost::variant<list...>;
};


template <typename Variant>
struct VariantTypeToTupleType;

template <typename... list>
struct VariantTypeToTupleType<boost::variant<list...>>
{
    using type = std::tuple<list...>;
};


template <typename T>
auto MakeVariant(const T & arg)
{
    return boost::variant<T>(arg);
}

template <typename T, typename = std::enable_if_t<IsCharType<T>::value>>
auto MakeVariant(const T * s)
{
    using str_t = std::basic_string<T>;
    return boost::variant<str_t>(str_t(s));
}


template <typename... Args>
auto MakeVariantVector(Args &&...  args)
{
    using unique_tuple_t = typename MakeUniqueElementTypeTuple<
                                        typename CharTypeToStringType<std::decay_t<decltype(args)>>::type...
                                    >::type;
    using element_t = typename TupleTypeToVariantType<unique_tuple_t>::type;

    std::vector<element_t> v;
    v.reserve(sizeof...(args));

    ForEachArgument(
            [&v](auto && e) { v.push_back(e); },
            std::forward<Args>(args)...
    );

    return v;
}


#endif //ROCKY_VARIANTUTILITY_H

