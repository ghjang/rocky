#include "../catch.hpp"

#include "rocky/muse/Interval.h"


TEST_CASE("NextHalfMusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<note_c_t<MusicalNote::Db>, NextHalfMusicalNoteT<MusicalNote::C>>(), "");
    static_assert(is_same<note_c_t<MusicalNote::C>, NextHalfMusicalNoteT<MusicalNote::B>>(), "");

    // perfect 4th
    static_assert(
            is_same<
                    note_c_t<MusicalNote::F>,
                    NestT<Quote<NextHalfMusicalNote>, note_c_t<MusicalNote::C>, 5>
                                                                                        >(),
            ""
    );

    // perfect 5th
    static_assert(
            is_same<
                    note_c_t<MusicalNote::G>,
                    NestT<Quote<NextHalfMusicalNote>, note_c_t<MusicalNote::C>, 7>
                                                                                        >(),
            ""
    );

    // 1-octave above
    static_assert(
            is_same<
                    note_c_t<MusicalNote::C>,
                    NestT<Quote<NextHalfMusicalNote>, note_c_t<MusicalNote::C>, 12>
                                                                                        >(),
            ""
    );

    // 2-octave above
    static_assert(
            is_same<
                    note_c_t<MusicalNote::C>,
                    NestT<Quote<NextHalfMusicalNote>, note_c_t<MusicalNote::C>, 24>
                                                                                        >(),
            ""
    );
}

TEST_CASE("PrevHalfMusicalNote", "[muse]")
{
    using std::is_same;

    static_assert(is_same<note_c_t<MusicalNote::B>, PrevHalfMusicalNoteT<MusicalNote::C>>(), "");
    static_assert(is_same<note_c_t<MusicalNote::Bb>, PrevHalfMusicalNoteT<MusicalNote::B>>(), "");

    // perfect 4th
    static_assert(
            is_same<
                    note_c_t<MusicalNote::G>,
                    NestT<Quote<PrevHalfMusicalNote>, note_c_t<MusicalNote::C>, 5>
                                                                                        >(),
            ""
    );

    // perfect 5th
    static_assert(
            is_same<
                    note_c_t<MusicalNote::F>,
                    NestT<Quote<PrevHalfMusicalNote>, note_c_t<MusicalNote::C>, 7>
                                                                                        >(),
            ""
    );

    // 1-octave below
    static_assert(
            is_same<
                    note_c_t<MusicalNote::C>,
                    NestT<Quote<PrevHalfMusicalNote>, note_c_t<MusicalNote::C>, 12>
                                                                                        >(),
            ""
    );

    // 2-octave below
    static_assert(
            is_same<
                    note_c_t<MusicalNote::C>,
                    NestT<Quote<PrevHalfMusicalNote>, note_c_t<MusicalNote::C>, 24>
                                                                                        >(),
            ""
    );
}

TEST_CASE("NextMusicalNoteT", "[muse]")
{
    using std::is_same;

    using note_list_t_0 = TypeList<
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Unison>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor2nd>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major2nd>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor3rd>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major3rd>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Diminished4th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Perfect4th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Augmented4th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Diminished5th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Perfect5th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Augmented5th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor6th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major6th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor7th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major7th>,
                                NextMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Octave>
                            >;

    using note_list_t_1 = TypeList<
                                note_c_t<MusicalNote::C>,
                                note_c_t<MusicalNote::Db>,
                                note_c_t<MusicalNote::D>,
                                note_c_t<MusicalNote::Eb>,
                                note_c_t<MusicalNote::E>,
                                note_c_t<MusicalNote::E>,
                                note_c_t<MusicalNote::F>,
                                note_c_t<MusicalNote::Gb>,
                                note_c_t<MusicalNote::Gb>,
                                note_c_t<MusicalNote::G>,
                                note_c_t<MusicalNote::Ab>,
                                note_c_t<MusicalNote::Ab>,
                                note_c_t<MusicalNote::A>,
                                note_c_t<MusicalNote::Bb>,
                                note_c_t<MusicalNote::B>,
                                note_c_t<MusicalNote::C>
                            >;

    static_assert(is_same<note_list_t_0, note_list_t_1>(), "");

    static_assert(
            is_same<
                    NextMusicalNoteT<MusicalNote::B, MusicalNoteInterval::Perfect5th>,
                    note_c_t<MusicalNote::Gb>
            >(),
            ""
    );
}

TEST_CASE("PrevMusicalNoteT", "[muse]")
{
    using std::is_same;

    using note_list_t_0 = TypeList<
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Unison>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor2nd>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major2nd>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor3rd>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major3rd>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Diminished4th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Perfect4th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Augmented4th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Diminished5th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Perfect5th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Augmented5th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor6th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major6th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Minor7th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Major7th>,
                                PrevMusicalNoteT<MusicalNote::C, MusicalNoteInterval::Octave>
                            >;

    using note_list_t_1 = TypeList<
                                note_c_t<MusicalNote::C>,
                                note_c_t<MusicalNote::B>,
                                note_c_t<MusicalNote::Bb>,
                                note_c_t<MusicalNote::A>,
                                note_c_t<MusicalNote::Ab>,
                                note_c_t<MusicalNote::Ab>,
                                note_c_t<MusicalNote::G>,
                                note_c_t<MusicalNote::Gb>,
                                note_c_t<MusicalNote::Gb>,
                                note_c_t<MusicalNote::F>,
                                note_c_t<MusicalNote::E>,
                                note_c_t<MusicalNote::E>,
                                note_c_t<MusicalNote::Eb>,
                                note_c_t<MusicalNote::D>,
                                note_c_t<MusicalNote::Db>,
                                note_c_t<MusicalNote::C>
                            >;

    static_assert(is_same<note_list_t_0, note_list_t_1>(), "");

    static_assert(
            is_same<
                    PrevMusicalNoteT<MusicalNote::B, MusicalNoteInterval::Perfect5th>,
                    note_c_t<MusicalNote::E>
            >(),
            ""
    );
}

