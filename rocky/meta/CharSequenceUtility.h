#ifndef ROCKY_CHARSEQUENCEUTILITY_H
#define ROCKY_CHARSEQUENCEUTILITY_H


#include "rocky/meta/IntegerSequenceUtility.h"


template <char... c>
using CharSequence = std::integer_sequence<char, c...>;


#endif //ROCKY_CHARSEQUENCEUTILITY_H

