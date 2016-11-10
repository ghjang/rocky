#include "../catch.hpp"

#include "rocky/muse/MusicalScale.h"
#include "rocky/muse/MusicalScalePrint.h"

#include "rocky/skull/Length.h"


TEST_CASE("MusicalScales length", "[muse]")
{
    static_assert(12 == Length<TwelveMajorScaleListT>());
}

TEST_CASE("Printing musical scales to console", "[muse]")
{
    // NOTE: just commented it out not to disrupt the console output.
    //PrintScaleList(TwelveMajorScaleListT());
}

TEST_CASE("Major Scale", "[muse]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TypeList<
                            pitch_class_c_t<PitchClass::C>,
                            pitch_class_c_t<PitchClass::D>,
                            pitch_class_c_t<PitchClass::E>,
                            pitch_class_c_t<PitchClass::F>,
                            pitch_class_c_t<PitchClass::G>,
                            pitch_class_c_t<PitchClass::A>,
                            pitch_class_c_t<PitchClass::B>
                    >,
                    MajorScaleT<PitchClass::C>
            >()
    );

    static_assert(
            is_same<
                    TypeList<
                            pitch_class_c_t<PitchClass::G>,
                            pitch_class_c_t<PitchClass::A>,
                            pitch_class_c_t<PitchClass::B>,
                            pitch_class_c_t<PitchClass::C>,
                            pitch_class_c_t<PitchClass::D>,
                            pitch_class_c_t<PitchClass::E>,
                            pitch_class_c_t<PitchClass::Gb>
                    >,
                    MajorScaleT<PitchClass::G>
            >()
    );
}

