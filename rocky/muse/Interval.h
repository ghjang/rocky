#ifndef ROCKY_MUSE_INTERVAL_H
#define ROCKY_MUSE_INTERVAL_H


#include "rocky/muse/MusicalNote.h"


template <typename note>
struct NextHalfMusicalNote;

template <MusicalNote note>
struct NextHalfMusicalNote<musical_note_c_t<note>>
        : type_is<musical_note_c_t<static_cast<MusicalNote>(static_cast<int>(note) + 1)>>
{ };

template <>
struct NextHalfMusicalNote<musical_note_c_t<MusicalNote::B>>
        : type_is<musical_note_c_t<MusicalNote::C>>
{ };


template <MusicalNote note>
using NextHalfMusicalNoteT = typename NextHalfMusicalNote<musical_note_c_t<note>>::type;


template <typename note>
struct PrevHalfMusicalNote;

template <MusicalNote note>
struct PrevHalfMusicalNote<musical_note_c_t<note>>
        : type_is<musical_note_c_t<static_cast<MusicalNote>(static_cast<int>(note) - 1)>>
{ };

template <>
struct PrevHalfMusicalNote<musical_note_c_t<MusicalNote::C>>
        : type_is<musical_note_c_t<MusicalNote::B>>
{ };


template <MusicalNote note>
using PrevHalfMusicalNoteT = typename PrevHalfMusicalNote<musical_note_c_t<note>>::type;


#endif //ROCKY_MUSE_INTERVAL_H

