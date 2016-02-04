#include "../catch.hpp"

#include "rocky/muse/MusicalScale.h"

#include "rocky/skull/Length.h"


TEST_CASE("MusicalScale", "[muse]")
{
    using std::is_same;

    static_assert(12 == Length<TwelveMajorScaleListT>(), "");

    PrintScaleList(TwelveMajorScaleListT());
}

