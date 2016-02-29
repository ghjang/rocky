#ifndef ROCKY_MUSE_INTERVAL_H
#define ROCKY_MUSE_INTERVAL_H


#include "rocky/wolca/Nest.h"
#include "rocky/muse/MusicalNote.h"


template <typename PitchClass>
struct NextPitchClass;

template <PitchClass pc>
struct NextPitchClass<pitch_class_c_t<pc>>
        : type_is<pitch_class_c_t<static_cast<PitchClass>(static_cast<int>(pc) + 1)>>
{ };

template <>
struct NextPitchClass<pitch_class_c_t<PitchClass::B>>
        : type_is<pitch_class_c_t<PitchClass::C>>
{ };


template <PitchClass pc>
using NextPitchClassT = typename NextPitchClass<pitch_class_c_t<pc>>::type;


template <typename PitchClass>
struct PrevPitchClass;

template <PitchClass pc>
struct PrevPitchClass<pitch_class_c_t<pc>>
        : type_is<pitch_class_c_t<static_cast<PitchClass>(static_cast<int>(pc) - 1)>>
{ };

template <>
struct PrevPitchClass<pitch_class_c_t<PitchClass::C>>
        : type_is<pitch_class_c_t<PitchClass::B>>
{ };


template <PitchClass pc>
using PrevPitchClassT = typename PrevPitchClass<pitch_class_c_t<pc>>::type;


enum struct PitchInterval : int
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


template <PitchInterval interval>
using interval_c_t = std::integral_constant<PitchInterval, interval>;


namespace Detail
{
    /**
     * @tparam F metafunction class to generate next musical note
     */
    template<typename F, typename PitchClass, typename Interval>
    struct NextPitchClassWithInterval;

    template<typename f, PitchClass pc, PitchInterval interval>
    struct NextPitchClassWithInterval<f, pitch_class_c_t<pc>, interval_c_t<interval>>
            : Nest<
                    f,
                    pitch_class_c_t<pc>,
                    std::integral_constant<
                            std::underlying_type_t<PitchInterval>,
                            static_cast<std::underlying_type_t<PitchInterval>>(interval)
                    >
              >
    { };
} // namespace Detail


template <PitchClass pc, PitchInterval interval>
using NextPitchClassWithIntervalT = typename Detail::NextPitchClassWithInterval<
                                                        Quote<NextPitchClass>,
                                                        pitch_class_c_t<pc>,
                                                        interval_c_t<interval>
                                                >::type;

template <PitchClass pc, PitchInterval interval>
using PrevPitchClassWithIntervalT = typename Detail::NextPitchClassWithInterval< Quote<PrevPitchClass>,
                                                        pitch_class_c_t<pc>,
                                                        interval_c_t<interval>
                                                >::type;


// TODO: add runtime functions operating on type instances.
//          interval between two pitches.
//          need to consider intervals above octaves.
//          need to change NextPitchClass's interfaces.


#endif //ROCKY_MUSE_INTERVAL_H

