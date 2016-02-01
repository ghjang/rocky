#ifndef ROCKY_WOLCA_ROTATE_H
#define ROCKY_WOLCA_ROTATE_H


#include "rocky/app/Rotate.h"


template <uint8_t n, typename... xs>
using RotateLeftT = RotateT<std::integral_constant<decltype(n * -1), n * -1>, xs...>;


template <uint8_t n, typename... xs>
using RotateRightT = RotateT<std::integral_constant<decltype(n), n>, xs...>;


#endif //ROCKY_WOLCA_ROTATE_H

