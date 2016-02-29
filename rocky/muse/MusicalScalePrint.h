#ifndef ROCKY_MUSE_MUSICALSCALEPRINT_H
#define ROCKY_MUSE_MUSICALSCALEPRINT_H


#include <iostream>

#include "rocky/base/ForEach.h"
#include "rocky/muse/MusicalScale.h"


template <PitchClass pc>
void PrintPitchClass(pitch_class_c_t<pc>)
{
    static char const * pitchClassNameStr[] = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
    std::cout << pitchClassNameStr[static_cast<int>(pc)];
}

template <PitchClass... pc>
void PrintScale(TypeList<pitch_class_c_t<pc>...>)
{
    auto n = sizeof...(pc) - 1;
    ForEachElementType(
            [&n](auto t) {
                PrintPitchClass(typename decltype(t)::type());
                if (n-- > 0) {
                    std::cout << '\t';
                }
            },
            TypeList<pitch_class_c_t<pc>...>()
    );
    std::cout << std::endl;
}

template <typename... scale>
void PrintScaleList(TypeList<scale...>)
{
    ForEachElementType(
            [](auto t) { PrintScale(typename decltype(t)::type()); },
            TypeList<scale...>()
    );
}


#endif //ROCKY_MUSE_MUSICALSCALEPRINT_H

