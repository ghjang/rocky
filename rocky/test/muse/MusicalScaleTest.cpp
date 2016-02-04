#include "../catch.hpp"

#include "rocky/muse/MusicalScale.h"
#include "rocky/muse/MusicalScalePrint.h"

#include "rocky/skull/Length.h"


TEST_CASE("MusicalScales length", "[muse]")
{
    static_assert(12 == Length<TwelveMajorScaleListT>(), "");
}

TEST_CASE("Printing musical scales to console", "[muse]")
{
    // NOTE: just commented it out not to disrupt the console output.
    //PrintScaleList(TwelveMajorScaleListT());
}

