#ifndef ROCKY_MUSE_INTERVAL_H
#define ROCKY_MUSE_INTERVAL_H


#include "rocky/wolca/Nest.h"
#include "rocky/muse/MusicalNote.h"


template <typename note>
struct NextHalfMusicalNote;

template <MusicalNote note>
struct NextHalfMusicalNote<note_c_t<note>>
        : type_is<note_c_t<static_cast<MusicalNote>(static_cast<int>(note) + 1)>>
{ };

template <>
struct NextHalfMusicalNote<note_c_t<MusicalNote::B>>
        : type_is<note_c_t<MusicalNote::C>>
{ };


template <MusicalNote note>
using NextHalfMusicalNoteT = typename NextHalfMusicalNote<note_c_t<note>>::type;


template <typename note>
struct PrevHalfMusicalNote;

template <MusicalNote note>
struct PrevHalfMusicalNote<note_c_t<note>>
        : type_is<note_c_t<static_cast<MusicalNote>(static_cast<int>(note) - 1)>>
{ };

template <>
struct PrevHalfMusicalNote<note_c_t<MusicalNote::C>>
        : type_is<note_c_t<MusicalNote::B>>
{ };


template <MusicalNote note>
using PrevHalfMusicalNoteT = typename PrevHalfMusicalNote<note_c_t<note>>::type;


enum struct MusicalNoteInterval : int
{
    Unison          = 0,
    Minor2nd        = 1,
    Major2nd        = 2,
    Minor3rd        = 3,
    Major3rd        = 4,
    Diminished4th   = 4,
    Perfect4th      = 5,
    Augmented4th    = 6,
    Diminished5th   = 6,
    Perfect5th      = 7,
    Augmented5th    = 8,
    Minor6th        = 8,
    Major6th        = 9,
    Minor7th        = 10,
    Major7th        = 11,
    Octave          = 12
};


namespace Detail
{
    /**
     * @tparam f metafunction class to generate next musical note
     */
    template<typename f, typename note, MusicalNoteInterval interval>
    struct NextMusicalNote;

    template<typename f, MusicalNote note, MusicalNoteInterval interval>
    struct NextMusicalNote<f, note_c_t<note>, interval>
            : Nest<
                    f,
                    note_c_t<note>,
                    std::integral_constant<
                            std::underlying_type_t<MusicalNoteInterval>,
                            static_cast<std::underlying_type_t<MusicalNoteInterval>>(interval)
                    >
            >
    { };
} // namespace Detail


template <MusicalNote note, MusicalNoteInterval interval>
using NextMusicalNoteT = typename Detail::NextMusicalNote<
                                                Quote<NextHalfMusicalNote>,
                                                note_c_t<note>,
                                                interval
                                    >::type;

template <MusicalNote note, MusicalNoteInterval interval>
using PrevMusicalNoteT = typename Detail::NextMusicalNote<
                                                Quote<PrevHalfMusicalNote>,
                                                note_c_t<note>,
                                                interval
                                    >::type;


#endif //ROCKY_MUSE_INTERVAL_H

