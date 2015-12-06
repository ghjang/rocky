#ifndef ROCKY_VARIANTUTILITY_H
#define ROCKY_VARIANTUTILITY_H


#include <type_traits>
#include <string>
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
struct CharPtrTypeToStrType
{
    using type = T;
};

template <std::size_t N>
struct CharPtrTypeToStrType<char [N]>
{
    using type = std::string;
};

template <std::size_t N>
struct CharPtrTypeToStrType<char const (&) [N]>
{
    using type = std::string;
};

template <>
struct CharPtrTypeToStrType<char const *>
{
    using type = std::string;
};

template <>
struct CharPtrTypeToStrType<char *>
{
    using type = std::string;
};

template <std::size_t N>
struct CharPtrTypeToStrType<wchar_t [N]>
{
    using type = std::wstring;
};

template <std::size_t N>
struct CharPtrTypeToStrType<wchar_t const (&) [N]>
{
    using type = std::wstring;
};

template <>
struct CharPtrTypeToStrType<wchar_t const *>
{
    using type = std::wstring;
};

template <>
struct CharPtrTypeToStrType<wchar_t *>
{
    using type = std::wstring;
};


template <typename T>
auto MakeVariant(const T & arg)
{
    return boost::variant<T>(arg);
}

auto MakeVariant(const char * s)
{
    return boost::variant<std::string>(std::string(s));
}

auto MakeVariant(const wchar_t * s)
{
    return boost::variant<std::wstring>(std::wstring(s));
}


template <typename... Args>
auto MakeVariantVector(const Args &...  args)
{
    using unique_tuple_t = typename MakeUniqueElementTypeTuple<
                                        typename CharPtrTypeToStrType<std::decay_t<decltype(args)>>::type...
                                    >::type;
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

