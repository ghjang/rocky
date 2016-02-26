#ifndef ROCKY_BASE_VOIDT_H
#define ROCKY_BASE_VOIDT_H


template <typename...>
using void_t = void;


template <template <typename...> class...>
using void_template_t = void;


#endif //ROCKY_BASE_VOIDT_H

