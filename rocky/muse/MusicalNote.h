#ifndef ROCKY_MUSE_MUSICALNOTE_H
#define ROCKY_MUSE_MUSICALNOTE_H


#include "rocky/base/TypeList.h"


enum struct MusicalNote : int
{
    C   = 0,
    Db  = 1,
    D   = 2,
    Eb  = 3,
    E   = 4,
    F   = 5,
    Gb  = 6,
    G   = 7,
    Ab  = 8,
    A   = 9,
    Bb  = 10,
    B   = 11
};


template <MusicalNote note>
using musical_note_c_t = std::integral_constant<MusicalNote, note>;


template <MusicalNote... note>
using MusicalNoteList = TypeList<musical_note_c_t<note>...>;


using TwelveHalfMusicalNoteList = MusicalNoteList<
                                        MusicalNote::C,
                                        MusicalNote::Db,
                                        MusicalNote::D,
                                        MusicalNote::Eb,
                                        MusicalNote::E,
                                        MusicalNote::F,
                                        MusicalNote::Gb,
                                        MusicalNote::G,
                                        MusicalNote::Ab,
                                        MusicalNote::A,
                                        MusicalNote::Bb,
                                        MusicalNote::B
                                    >;


#endif //ROCKY_MUSE_MUSICALNOTE_H

