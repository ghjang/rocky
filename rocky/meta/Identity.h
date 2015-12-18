#ifndef ROCKY_IDENTITY_H
#define ROCKY_IDENTITY_H


template <typename T>
struct Identity
{
    using type = T;
};


// NOTE: type_is is more descriptive than Identity in some cases.
template <typename T>
using type_is = Identity<T>;


#endif //ROCKY_IDENTITY_H

