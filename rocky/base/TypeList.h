#ifndef ROCKY_BASE_TYPELIST_H
#define ROCKY_BASE_TYPELIST_H


#include <type_traits>

#include "rocky/base/Identity.h"


template <typename... xs>
struct TypeList
{ };

template <typename... xs>
using TL = TypeList<xs...>;


namespace Detail
{
    /**
     * NOTE: for internal use only
     */
    struct __Guard__
    { };
} // namespace Detail


template <typename... xs>
struct TypeListSize : std::integral_constant<std::size_t, sizeof...(xs)>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct TypeListSize<TypeListContainer<xs...>> : TypeListSize<xs...>
{ };


template <typename f>
struct FunctionParameterListSize;

template <typename r, typename... params>
struct FunctionParameterListSize<r (params...)> : std::integral_constant<std::size_t, sizeof...(params)>
{ };

template <typename r, typename... params>
struct FunctionParameterListSize<r (&) (params...)> : FunctionParameterListSize<r (params...)>
{ };

template <typename r, typename... params>
struct FunctionParameterListSize<r (*) (params...)> : FunctionParameterListSize<r (params...)>
{ };


template <typename SourceTypeList, template <typename...> class TargetTypeListContainer>
struct ReplaceTypeListContainer;

template <template <typename...> class S, typename... xs>
struct ReplaceTypeListContainer<S<xs...>, S> : type_is<S<xs...>>
{ };

template <template <typename...> class S, typename... xs, template <typename...> class T>
struct ReplaceTypeListContainer<S<xs...>, T> : type_is<T<xs...>>
{ };

template <typename SourceTypeList, template <typename...> class TargetTypeListContainer>
using ReplaceTypeListContainerT = typename ReplaceTypeListContainer<SourceTypeList, TargetTypeListContainer>::type;


/**
 * QuoteReplaceTypeListContainer is a metafunction class.
 *
 * @tparam f metafunction
 */
template <template <typename...> class f>
struct QuoteReplaceTypeListContainer
{
    template <typename xs>
    struct Apply : ReplaceTypeListContainer<xs, f>
    { };
};


#endif //ROCKY_BASE_TYPELIST_H

