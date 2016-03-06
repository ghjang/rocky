#ifndef ROCKY_BASE_TYPERELATION_H
#define ROCKY_BASE_TYPERELATION_H


#include "rocky/base/TypeName.h"
#include "rocky/base/ForEach.h"


template <typename F, template <typename...> class TypeListContainer, typename... xs>
void ForEachChildElementTypeInPreOrder(F && f, TypeListContainer<xs...>);


namespace Detail
{
    template<typename T, typename = void>
    struct PreOrderTypeTraversalHelper
    {
        template<typename F>
        void operator()(F & f) const
        {
            f(type_c<T>);
        }
    };

    template<typename T>
    struct PreOrderTypeTraversalHelper<T, std::enable_if_t<IsTypeListContainer<T>::value>>
    {
        template<typename F>
        void operator()(F & f) const
        {
            ForEachChildElementTypeInPreOrder(f, T());
        }
    };
} // namespace Detail


template <typename F, template <typename...> class TypeListContainer, typename... xs>
void ForEachChildElementTypeInPreOrder(F && f, TypeListContainer<xs...>)
{
    f(type_c<TypeListContainer<xs...>>);

    ForEachElementType(
            [&f](auto t) {
                using arg_type_t = typename decltype(t)::type;
                Detail::PreOrderTypeTraversalHelper<arg_type_t>()(f);
            },
            TypeList<xs...>()
    );
}


#endif //ROCKY_BASE_TYPERELATION_H

