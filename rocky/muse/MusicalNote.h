#ifndef ROCKY_MUSE_PITCHCLASS_H
#define ROCKY_MUSE_PITCHCLASS_H


#include "rocky/base/TypeList.h"


enum struct PitchClass : int
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


template <PitchClass pc>
using pitch_class_c_t = std::integral_constant<PitchClass, pc>;


template <PitchClass... pc>
using PitchClassList = TypeList<pitch_class_c_t<pc>...>;


using TwelvePitchClassList = PitchClassList<
                                    PitchClass::C,
                                    PitchClass::Db,
                                    PitchClass::D,
                                    PitchClass::Eb,
                                    PitchClass::E,
                                    PitchClass::F,
                                    PitchClass::Gb,
                                    PitchClass::G,
                                    PitchClass::Ab,
                                    PitchClass::A,
                                    PitchClass::Bb,
                                    PitchClass::B
                                >;


#endif //ROCKY_MUSE_PITCHCLASS_H

