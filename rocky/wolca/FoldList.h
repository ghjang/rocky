#ifndef ROCKY_WOLCA_FOLDLIST_H
#define ROCKY_WOLCA_FOLDLIST_H


#include "rocky/base/TypeList.h"
#include "rocky/base/HasMember.h"


// accumulation

/**
 * assumed that F is op:
 *  (...(init op t0) op t1) op t2)... op tn)
 */


namespace Detail
{
    template <typename rs, template <typename, typename> class f, typename init, typename... xs>
    struct FoldListImpl;

    template <typename... rs, template <typename, typename> class f, typename last>
    struct FoldListImpl<TypeList<rs...>, f, last>
            : type_is<TypeList<rs...>>
    { };

    template <typename... rs, template <typename, typename> class f, typename init, typename x, typename... xs>
    struct FoldListImpl<TypeList<rs...>, f, init, x, xs...>
            : FoldListImpl<TypeList<rs..., typename f<init, x>::type>, f, typename f<init, x>::type, xs...>
    { };
} // namespace Detail


// NOTE: FoldList is fold-left.
template <template <typename, typename> class f, typename init, typename... xs>
struct FoldList;

template <template <typename, typename> class f, typename init, typename x, typename... xs>
struct FoldList<f, init, x, xs...>
        : Detail::FoldListImpl<TypeList<init, typename f<init, x>::type>, f, typename f<init, x>::type, xs...>
{
    static_assert(HasTypeMember<f<init, x>>(), "f should have 'type' member.");
};

template
<
        template <typename, typename> class f,
        typename init,
        template <typename...> class TypeListContainer,
        typename... xs
>
struct FoldList<f, init, TypeListContainer<xs...>>
        : ReplaceTypeListContainer<typename FoldList<f, init, xs...>::type, TypeListContainer>
{ };


template <template <typename, typename> class f, typename init, typename... xs>
using FoldListT = typename FoldList<f, init, xs...>::type;


#endif //ROCKY_WOLCA_FOLDLIST_H

