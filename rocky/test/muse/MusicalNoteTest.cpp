#include "../catch.hpp"

#include "rocky/muse/MusicalNote.h"

#include "rocky/skull/Head.h"
#include "rocky/skull/Last.h"

#include "rocky/wolca/Nest.h"


TEST_CASE("MusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<musical_note_c_t<MusicalNote::C>, HeadT<TwelveHalfMusicalNoteList>>(), "");
    static_assert(is_same<musical_note_c_t<MusicalNote::B>, LastT<TwelveHalfMusicalNoteList>>(), "");
}

TEST_CASE("NextHalfMusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<musical_note_c_t<MusicalNote::Db>, NextHalfMusicalNoteT<MusicalNote::C>>(), "");
    static_assert(is_same<musical_note_c_t<MusicalNote::C>, NextHalfMusicalNoteT<MusicalNote::B>>(), "");

    // perfect 4th
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::F>,
                    NestT<Quote<NextHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 5>
            >(),
            ""
    );

    // perfect 5th
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::G>,
                    NestT<Quote<NextHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 7>
            >(),
            ""
    );

    // 1-octave above
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::C>,
                    NestT<Quote<NextHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 12>
            >(),
            ""
    );

    // 2-octave above
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::C>,
                    NestT<Quote<NextHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 24>
            >(),
            ""
    );
}

TEST_CASE("PrevHalfMusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<musical_note_c_t<MusicalNote::B>, PrevHalfMusicalNoteT<MusicalNote::C>>(), "");
    static_assert(is_same<musical_note_c_t<MusicalNote::Bb>, PrevHalfMusicalNoteT<MusicalNote::B>>(), "");

    // perfect 4th
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::G>,
                    NestT<Quote<PrevHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 5>
            >(),
            ""
    );

    // perfect 5th
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::F>,
                    NestT<Quote<PrevHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 7>
            >(),
            ""
    );

    // 1-octave below
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::C>,
                    NestT<Quote<PrevHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 12>
            >(),
            ""
    );

    // 2-octave below
    static_assert(
            is_same<
                    musical_note_c_t<MusicalNote::C>,
                    NestT<Quote<PrevHalfMusicalNote>, musical_note_c_t<MusicalNote::C>, 24>
            >(),
            ""
    );
}

