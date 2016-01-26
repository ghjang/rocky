#ifndef ROCKY_BASE_MULTIPLEINHERITANCE_H
#define ROCKY_BASE_MULTIPLEINHERITANCE_H


template <typename... BaseTypeList>
struct MultipleInheritance : BaseTypeList...
{
    using type = MultipleInheritance;
};


#endif //ROCKY_BASE_MULTIPLEINHERITANCE_H

