#include "../catch.hpp"

#include "rocky/muse/MusicalNote.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Last.h"


TEST_CASE("MusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<musical_note_c_t<MusicalNote::C>, HeadT<TwelveHalfMusicalNoteList>>(), "");
    static_assert(is_same<musical_note_c_t<MusicalNote::B>, LastT<TwelveHalfMusicalNoteList>>(), "");
}

