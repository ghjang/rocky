#include "../catch.hpp"

#include "rocky/muse/Interval.h"


TEST_CASE("NextPitchClass", "[muse]")
{
    using std::is_same;

    static_assert(is_same<pitch_class_c_t<PitchClass::Db>, NextPitchClassT<PitchClass::C>>());
    static_assert(is_same<pitch_class_c_t<PitchClass::C>, NextPitchClassT<PitchClass::B>>());

    // perfect 4th
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::F>,
                    NestT<Quote<NextPitchClass>, pitch_class_c_t<PitchClass::C>, 5>
            >()
    );

    // perfect 5th
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::G>,
                    NestT<Quote<NextPitchClass>, pitch_class_c_t<PitchClass::C>, 7>
            >()
    );

    // 1-octave above
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::C>,
                    NestT<Quote<NextPitchClass>, pitch_class_c_t<PitchClass::C>, 12>
            >()
    );

    // 2-octave above
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::C>,
                    NestT<Quote<NextPitchClass>, pitch_class_c_t<PitchClass::C>, 24>
            >()
    );
}

TEST_CASE("PrevPitchClass", "[muse]")
{
    using std::is_same;

    static_assert(is_same<pitch_class_c_t<PitchClass::B>, PrevPitchClassT<PitchClass::C>>());
    static_assert(is_same<pitch_class_c_t<PitchClass::Bb>, PrevPitchClassT<PitchClass::B>>());

    // perfect 4th
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::G>,
                    NestT<Quote<PrevPitchClass>, pitch_class_c_t<PitchClass::C>, 5>
            >()
    );

    // perfect 5th
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::F>,
                    NestT<Quote<PrevPitchClass>, pitch_class_c_t<PitchClass::C>, 7>
            >()
    );

    // 1-octave below
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::C>,
                    NestT<Quote<PrevPitchClass>, pitch_class_c_t<PitchClass::C>, 12>
            >()
    );

    // 2-octave below
    static_assert(
            is_same<
                    pitch_class_c_t<PitchClass::C>,
                    NestT<Quote<PrevPitchClass>, pitch_class_c_t<PitchClass::C>, 24>
            >()
    );
}

TEST_CASE("NextPitchClassWithIntervalT", "[muse]")
{
    using std::is_same;

    using pc_list_t_0 = TypeList<
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Unison>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor2nd>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major2nd>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor3rd>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major3rd>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Diminished4th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Perfect4th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Augmented4th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Diminished5th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Perfect5th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Augmented5th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor6th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major6th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor7th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major7th>,
                                NextPitchClassWithIntervalT<PitchClass::C, PitchInterval::Octave>
                            >;

    using pc_list_t_1 = TypeList<
                                pitch_class_c_t<PitchClass::C>,
                                pitch_class_c_t<PitchClass::Db>,
                                pitch_class_c_t<PitchClass::D>,
                                pitch_class_c_t<PitchClass::Eb>,
                                pitch_class_c_t<PitchClass::E>,
                                pitch_class_c_t<PitchClass::E>,
                                pitch_class_c_t<PitchClass::F>,
                                pitch_class_c_t<PitchClass::Gb>,
                                pitch_class_c_t<PitchClass::Gb>,
                                pitch_class_c_t<PitchClass::G>,
                                pitch_class_c_t<PitchClass::Ab>,
                                pitch_class_c_t<PitchClass::Ab>,
                                pitch_class_c_t<PitchClass::A>,
                                pitch_class_c_t<PitchClass::Bb>,
                                pitch_class_c_t<PitchClass::B>,
                                pitch_class_c_t<PitchClass::C>
                            >;

    static_assert(is_same<pc_list_t_0, pc_list_t_1>());

    static_assert(
            is_same<
                    NextPitchClassWithIntervalT<PitchClass::B, PitchInterval::Perfect5th>,
                    pitch_class_c_t<PitchClass::Gb>
            >()
    );
}

TEST_CASE("PrevPitchClassWithIntervalT", "[muse]")
{
    using std::is_same;

    using pc_list_t_0 = TypeList<
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Unison>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor2nd>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major2nd>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor3rd>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major3rd>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Diminished4th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Perfect4th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Augmented4th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Diminished5th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Perfect5th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Augmented5th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor6th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major6th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Minor7th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Major7th>,
                                PrevPitchClassWithIntervalT<PitchClass::C, PitchInterval::Octave>
                            >;

    using pc_list_t_1 = TypeList<
                                pitch_class_c_t<PitchClass::C>,
                                pitch_class_c_t<PitchClass::B>,
                                pitch_class_c_t<PitchClass::Bb>,
                                pitch_class_c_t<PitchClass::A>,
                                pitch_class_c_t<PitchClass::Ab>,
                                pitch_class_c_t<PitchClass::Ab>,
                                pitch_class_c_t<PitchClass::G>,
                                pitch_class_c_t<PitchClass::Gb>,
                                pitch_class_c_t<PitchClass::Gb>,
                                pitch_class_c_t<PitchClass::F>,
                                pitch_class_c_t<PitchClass::E>,
                                pitch_class_c_t<PitchClass::E>,
                                pitch_class_c_t<PitchClass::Eb>,
                                pitch_class_c_t<PitchClass::D>,
                                pitch_class_c_t<PitchClass::Db>,
                                pitch_class_c_t<PitchClass::C>
                            >;

    static_assert(is_same<pc_list_t_0, pc_list_t_1>());

    static_assert(
            is_same<
                    PrevPitchClassWithIntervalT<PitchClass::B, PitchInterval::Perfect5th>,
                    pitch_class_c_t<PitchClass::E>
            >()
    );
}

