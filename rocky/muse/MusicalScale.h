#ifndef ROCKY_MUSE_MUSICALSCALE_H
#define ROCKY_MUSE_MUSICALSCALE_H


#include "rocky/base/TypeComposition.h"
#include "rocky/skull/Map.h"
#include "rocky/wolca/NestList.h"
#include "rocky/app/Rotate.h"
#include "rocky/app/Extract.h"
#include "rocky/app/Find.h"
#include "rocky/muse/MusicalNote.h"


using MajorScalePitchClassIndexSequenceT = std::index_sequence<0, 2, 4, 5, 7, 9, 11>;

// TODO: add all the scale note indices.
//using MinorScalePitchClassIndexSequenceT = std::index_sequence<0, 2, 4, 5, 7, 9, 11>;


using TwelveMajorScaleListT = MapT<
                                    BindFirst<Quote<Extract>, MajorScalePitchClassIndexSequenceT>,
                                    NestListT<
                                            BindFirst<Quote<Rotate>, std::integral_constant<int, -1>>,
                                            TwelvePitchClassList,
                                            11
                                    >
                              >;


template <typename rootPitchClass>
struct MajorScale;

template <PitchClass rootPitchClass>
struct MajorScale<pitch_class_c_t<rootPitchClass>>
        : Apply<
                Compose<
                        BindFirst<Quote<Extract>, MajorScalePitchClassIndexSequenceT>,
                        Quote<Rotate>
                >,
                std::integral_constant<int, -Find<pitch_class_c_t<rootPitchClass>, TwelvePitchClassList>::value>,
                TwelvePitchClassList
          >
{ };


template <PitchClass rootPitchClass>
using MajorScaleT = typename MajorScale<pitch_class_c_t<rootPitchClass>>::type;


#endif //ROCKY_MUSE_MUSICALSCALE_H

