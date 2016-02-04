#ifndef ROCKY_MUSE_MUSICALSCALEPRINT_H
#define ROCKY_MUSE_MUSICALSCALEPRINT_H


#include <iostream>

#include "rocky/base/ForEach.h"
#include "rocky/muse/MusicalScale.h"


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


#endif //ROCKY_MUSE_MUSICALSCALEPRINT_H

