#ifndef ROCKY_MULTIPLEINHERITANCE_H
#define ROCKY_MULTIPLEINHERITANCE_H


template <typename... BaseTypeList>
struct MultipleInheritance : BaseTypeList...
{
    using type = MultipleInheritance;
};


#endif //ROCKY_MULTIPLEINHERITANCE_H

