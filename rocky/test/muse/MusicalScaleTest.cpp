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

TEST_CASE("Major Scale", "[muse]")
{
    using std::is_same;

    static_assert(
            is_same<
                    TypeList<
                            note_c_t<MusicalNote::C>,
                            note_c_t<MusicalNote::D>,
                            note_c_t<MusicalNote::E>,
                            note_c_t<MusicalNote::F>,
                            note_c_t<MusicalNote::G>,
                            note_c_t<MusicalNote::A>,
                            note_c_t<MusicalNote::B>
                    >,
                    MajorScaleT<MusicalNote::C>
            >(),
            ""
    );

    static_assert(
            is_same<
                    TypeList<
                            note_c_t<MusicalNote::G>,
                            note_c_t<MusicalNote::A>,
                            note_c_t<MusicalNote::B>,
                            note_c_t<MusicalNote::C>,
                            note_c_t<MusicalNote::D>,
                            note_c_t<MusicalNote::E>,
                            note_c_t<MusicalNote::Gb>
                    >,
                    MajorScaleT<MusicalNote::G>
            >(),
            ""
    );
}

