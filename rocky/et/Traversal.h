#ifndef ROCKY_ET_TRAVERSAL_H
#define ROCKY_ET_TRAVERSAL_H


#include <type_traits>
#include <functional>

#include "rocky/et/ExpressionTemplateFwd.h"


//==============================================================================
enum struct NodePositionType
{
    Null,
    Root,
    LeftChild,
    RightChild
};


//==============================================================================
#include "rocky/et/PassiveIterator.h"
#include "rocky/et/ActiveIterator.h"


#endif // ROCKY_ET_TRAVERSAL_H
