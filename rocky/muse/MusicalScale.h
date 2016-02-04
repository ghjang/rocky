#ifndef ROCKY_MUSE_MUSICALSCALE_H
#define ROCKY_MUSE_MUSICALSCALE_H


#include "rocky/skull/Map.h"
#include "rocky/wolca/NestList.h"
#include "rocky/app/Rotate.h"
#include "rocky/app/Extract.h"
#include "rocky/muse/MusicalNote.h"


namespace Detail
{
    template <typename NoteList>
    struct RotateLeftNote;

    template <MusicalNote... Note>
    struct RotateLeftNote<TypeList<musical_note_c_t<Note>...>>
            : Rotate<std::integral_constant<int, -1>, TypeList<musical_note_c_t<Note>...>>
    { };


    using MajorScaleNoteIndexSequenceT = std::index_sequence<0, 2, 4, 5, 7, 9, 11>;


    template <typename NoteIndexSequence>
    struct ExtractNote
    {
        template <typename NoteList>
        struct DoExtract;

        template <MusicalNote... Note>
        struct DoExtract<TypeList<musical_note_c_t<Note>...>>
                : Extract<NoteIndexSequence, TypeList<musical_note_c_t<Note>...>>
        { };
    };
} // namespace Detail


using TwelveMajorScaleListT = MapT<
                                    Detail::ExtractNote<Detail::MajorScaleNoteIndexSequenceT>::template DoExtract,
                                    NestListT<Detail::RotateLeftNote, TwelveHalfMusicalNoteList, 11>
                              >;


#endif //ROCKY_MUSE_MUSICALSCALE_H

