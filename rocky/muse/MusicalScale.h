#ifndef ROCKY_MUSE_MUSICALSCALE_H
#define ROCKY_MUSE_MUSICALSCALE_H


#include <iostream>

#include "rocky/base/ForEach.h"
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

    template <typename... Note>
    struct ExtractNote<TypeList<Note...>>
            : Extract<MajorScaleNoteIndexSequenceT, TypeList<Note...>>
    { };
} // namespace Detail


using TwelveMajorScaleListT = MapT<
                                    Detail::ExtractNote,
                                    NestListT<Detail::RotateLeftNote, TwelveHalfMusicalNoteList, 11>
                              >;


template <MusicalNote Note>
void PrintNote(musical_note_c_t<Note>)
{
    static char const * noteNameStr[] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
    std::cout << noteNameStr[static_cast<int>(Note)];
}

template <MusicalNote... Note>
void PrintScale(TypeList<musical_note_c_t<Note>...>)
{
    auto n = sizeof...(Note) - 1;
    ForEachElementType(
            [&n](auto t) {
                PrintNote(typename decltype(t)::type());
                if (n-- > 0) {
                    std::cout << '\t';
                }
            },
            TypeList<musical_note_c_t<Note>...>()
    );
    std::cout << std::endl;
}

template <typename... Scale>
void PrintScaleList(TypeList<Scale...>)
{
    ForEachElementType(
            [](auto t) { PrintScale(typename decltype(t)::type()); },
            TypeList<Scale...>()
    );
}


#endif //ROCKY_MUSE_MUSICALSCALE_H

