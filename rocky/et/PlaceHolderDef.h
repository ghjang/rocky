#ifndef ROCKY_ET_PLACE_HOLDER_DEF_H
#define ROCKY_ET_PLACE_HOLDER_DEF_H


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef PLACE_HOLDER_MAX_SIZE
#   define PLACE_HOLDER_MAX_SIZE 8
#endif // PLACE_HOLDER_MAX_SIZE

#define ET_place_holder(z, n, unused) static place_holder<n> BOOST_PP_CAT(_, n){};

#define BOOST_PP_LOCAL_MACRO(n)     ET_place_holder(~, n, ~)
#define BOOST_PP_LOCAL_LIMITS       (1, PLACE_HOLDER_MAX_SIZE)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_PP_LOCAL_LIMITS
#undef BOOST_PP_LOCAL_MACRO
#undef ET_place_holder


#endif // ROCKY_ET_PLACE_HOLDER_DEF_H
