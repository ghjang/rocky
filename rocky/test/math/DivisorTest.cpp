#include "../catch.hpp"

#include "rocky/math/Divisor.h"


TEST_CASE("Divisor", "[math]")
{
    using std::is_same;
    using std::integer_sequence;

    static_assert(
            is_same<
                    TypeList<>,
                    DivisorT<int_c_t<0>>
            >()
    );

    static_assert(
            is_same<
                    TypeList<int_c_t<1>, int_c_t<2>, int_c_t<4>, int_c_t<5>, int_c_t<10>, int_c_t<20>>,
                    DivisorT<int_c_t<20>>
            >()
    );

    static_assert(
            is_same<
            TypeList<int_c_t<1>, int_c_t<2>, int_c_t<4>, int_c_t<5>, int_c_t<10>, int_c_t<20>>,
            DivisorT<int_c_t<-20>>
            >()
    );

    static_assert(
            is_same<
            TypeList<int_c_t<1>, int_c_t<2>, int_c_t<4>, int_c_t<5>, int_c_t<10>, int_c_t<20>>,
            MakeDivisorTypeListT<-20>
            >()
    );

    static_assert(
            is_same<
            integer_sequence<int, 1, 2, 4, 5, 10, 20>,
            MakeDivisorSequenceT<-20>
            >()
    );
}

