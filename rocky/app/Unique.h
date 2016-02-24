#ifndef ROCKY_APP_UNIQUE_H
#define ROCKY_APP_UNIQUE_H


#include "rocky/skull/FoldL.h"
#include "rocky/skull/Elem.h"
#include "rocky/skull/Length.h"
#include "rocky/app/Find.h"


template <typename... xs>
struct Unique;

template <typename... xs>
struct Unique
{
private:
    using init_t = TypeList<>;

    template <typename lhs, typename rhs>
    struct AppendTypeIfNotExist;

    template <typename... lhs, typename rhs>
    struct AppendTypeIfNotExist<TypeList<lhs...>, rhs>
                : std::conditional<
                        !Elem<rhs, lhs...>(),
                        TypeList<lhs..., rhs>,
                        TypeList<lhs...>
                    >
    { };

public:
    using type = FoldLT<Quote<AppendTypeIfNotExist>, init_t, xs...>;
};


template <typename... xs>
using UniqueT = typename Unique<xs...>::type;


template <typename x, typename y>
struct Unique<std::pair<x, y>> : Unique<x, y>
{ };

template <template <typename...> class TypeListContainer, typename... xs>
struct Unique<TypeListContainer<xs...>>
        : ReplaceTypeListContainer<UniqueT<xs...>, TypeListContainer>
{ };


template <typename... xs>
struct HasSameType
        : std::conditional_t<
                Length<UniqueT<xs...>>() == 1,
                std::true_type,
                std::false_type
        >
{ };

template <>
struct HasSameType<> : std::true_type
{ };

template <template <typename...> class TypeListContainer>
struct HasSameType<TypeListContainer<>> : std::true_type
{ };


#endif //ROCKY_APP_UNIQUE_H

