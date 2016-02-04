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

    template <typename... Note>
    struct RotateLeftNote<TypeList<Note...>>
            : Rotate<std::integral_constant<int, -1>, TypeList<Note...>>
    { };


    using MajorScaleNoteIndexSequenceT = std::index_sequence<0, 2, 4, 5, 7, 9, 11>;


    template <typename NoteList>
    struct ExtractNote;

    template <MusicalNote... Note>
    struct ExtractNote<TypeList<musical_note_c_t<Note>...>>
            : Extract<MajorScaleNoteIndexSequenceT, TypeList<musical_note_c_t<Note>...>>
    { };
} // namespace Detail


using TwelveMajorScaleListT = MapT<
                                    Detail::ExtractNote,
                                    NestListT<Detail::RotateLeftNote, TwelveHalfMusicalNoteList, 11>
                              >;


#endif //ROCKY_MUSE_MUSICALSCALE_H

