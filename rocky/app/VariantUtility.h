#ifndef ROCKY_APP_VARIANTUTILITY_H
#define ROCKY_APP_VARIANTUTILITY_H


#include <string>
#include <vector>

#include "boost/variant.hpp"

#include "rocky/base/TypeUtility.h"
#include "rocky/base/ForEachArgument.h"
#include "rocky/app/Unique.h"


template <typename... xs>
struct ToVariantType : type_is<boost::variant<xs...>>
{ };

template <typename... xs>
using ToVariantTypeT = typename ToVariantType<xs...>::type;

template <typename... xs>
struct ToVariantType<TypeList<xs...>> : ToVariantType<xs...>
{ };

template <typename... xs>
struct ToVariantType<std::tuple<xs...>> : ToVariantType<xs...>
{ };


template <typename Variant>
struct ToTupleType;

template <typename... list>
struct ToTupleType<boost::variant<list...>>
        : type_is<std::tuple<list...>>
{ };


template <typename T>
auto MakeVariant(T const& arg)
{
    return boost::variant<T>(arg);
}

template <typename T, typename = std::enable_if_t<IsCharType<T>::value>>
auto MakeVariant(T const* s)
{
    using str_t = std::basic_string<T>;
    return boost::variant<str_t>(str_t(s));
}


template <typename... Args>
auto MakeVariantVector(Args &&...  args)
{
    using unique_t = UniqueT<CharTypeToStringTypeT<std::decay_t<decltype(args)>>...>;
    using element_t = ToVariantTypeT<unique_t>;

    std::vector<element_t> v;
    v.reserve(sizeof...(args));

    ForEachArgument(
            [&v](auto && e) { v.push_back(e); },
            std::forward<Args>(args)...
    );

    return v;
}


#endif //ROCKY_APP_VARIANTUTILITY_H

