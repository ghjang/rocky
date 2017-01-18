#ifndef ROCKY_ET_REPLACE_OP_TAG_H
#define ROCKY_ET_REPLACE_OP_TAG_H


#include "rocky/base/Identity.h"
#include "rocky/et/ExpressionTemplateFwd.h"


template <typename Expr, typename SrcOpTag, typename TargetOpTag>
struct ReplaceOpTag;


template <typename Derived, typename SrcOpTag, typename TargetOpTag>
struct ReplaceOpTag<terminal<Derived>, SrcOpTag, TargetOpTag>
        : type_is<terminal<Derived>>
{ };

template <std::size_t i, typename SrcOpTag, typename TargetOpTag>
struct ReplaceOpTag<place_holder<i>, SrcOpTag, TargetOpTag>
        : type_is<place_holder<i>>
{ };

template <bool IsValRValRef, typename T, typename SrcOpTag, typename TargetOpTag>
struct ReplaceOpTag<value_holder<IsValRValRef, T>, SrcOpTag, TargetOpTag>
        : type_is<value_holder<IsValRValRef, T>>
{ };

template <typename SrcOpTag, typename TargetOpTag>
struct ReplaceOpTag<null_terminal, SrcOpTag, TargetOpTag>
        : type_is<null_terminal>
{ };


template
<
    typename Left, typename SrcOpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    template <typename> class Operation,
    template <typename, typename, bool, bool> class Storage,
    typename TargetOpTag
>
struct ReplaceOpTag<
            expression<
                Left, SrcOpTag, Right,
                IsLeftRValRef, IsRightRValRef,
                Operation,
                Storage
            >,
            SrcOpTag,
            TargetOpTag
       > : type_is<
                expression<
                    typename ReplaceOpTag<Left, SrcOpTag, TargetOpTag>::type,
                    TargetOpTag,    // replace SrcOpTag with TargetOpTag
                    typename ReplaceOpTag<Right, SrcOpTag, TargetOpTag>::type,
                    IsLeftRValRef, IsRightRValRef,
                    Operation,
                    Storage
                >
           >
{ };

template
<
    typename Left, typename OpTag, typename Right, bool IsLeftRValRef, bool IsRightRValRef,
    template <typename> class Operation,
    template <typename, typename, bool, bool> class Storage,
    typename SrcOpTag,
    typename TargetOpTag
>
struct ReplaceOpTag<
            expression<
                Left, OpTag, Right,
                IsLeftRValRef, IsRightRValRef,
                Operation,
                Storage
            >,
            SrcOpTag,
            TargetOpTag
       > : type_is<
                expression<
                    typename ReplaceOpTag<Left, SrcOpTag, TargetOpTag>::type,
                    OpTag,  // preserve OpTag
                    typename ReplaceOpTag<Right, SrcOpTag, TargetOpTag>::type,
                    IsLeftRValRef, IsRightRValRef,
                    Operation,
                    Storage
                >
           >
{ };


template <typename Expr, typename SrcOpTag, typename TargetOpTag>
using ReplaceOpTagT = typename ReplaceOpTag<Expr, SrcOpTag, TargetOpTag>::type;


#endif // ROCKY_ET_REPLACE_OP_TAG_H
