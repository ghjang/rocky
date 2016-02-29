#include "../catch.hpp"

#include "rocky/muse/PitchClass.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Last.h"


TEST_CASE("PitchClass", "[muse]")
{
    using std::is_same;

    static_assert(is_same<pitch_class_c_t<PitchClass::C>, HeadT<TwelvePitchClassList>>(), "");
    static_assert(is_same<pitch_class_c_t<PitchClass::B>, LastT<TwelvePitchClassList>>(), "");
}

