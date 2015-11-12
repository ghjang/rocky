#ifndef ROCKY_WRAPTYPEMEMBER_H
#define ROCKY_WRAPTYPEMEMBER_H

template <typename T>
struct WrapAsTypeMember
{
    using type = T;
};

#endif //ROCKY_WRAPTYPEMEMBER_H

