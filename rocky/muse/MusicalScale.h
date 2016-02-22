#ifndef ROCKY_MUSE_MUSICALSCALE_H
#define ROCKY_MUSE_MUSICALSCALE_H


#include "rocky/base/TypeComposition.h"
#include "rocky/skull/Map.h"
#include "rocky/wolca/NestList.h"
#include "rocky/app/Rotate.h"
#include "rocky/app/Extract.h"
#include "rocky/app/Find.h"
#include "rocky/muse/MusicalNote.h"


using MajorScaleNoteIndexSequenceT = std::index_sequence<0, 2, 4, 5, 7, 9, 11>;


using TwelveMajorScaleListT = MapT<
                                    BindFirst<Quote<Extract>, MajorScaleNoteIndexSequenceT>,
                                    NestListT<
                                            BindFirst<Quote<Rotate>, std::integral_constant<int, -1>>,
                                            TwelveHalfMusicalNoteList,
                                            11
                                    >
                              >;


template <typename rootNote>
struct MajorScale;

template <MusicalNote rootNote>
struct MajorScale<note_c_t<rootNote>>
        : Apply<
                Compose<
                        BindFirst<Quote<Extract>, MajorScaleNoteIndexSequenceT>,
                        Quote<RotateWithTypeListUnpack>
                >,
                std::integral_constant<int, -Find<note_c_t<rootNote>, TwelveHalfMusicalNoteList>::value>,
                TwelveHalfMusicalNoteList
          >
{ };


template <MusicalNote rootNote>
using MajorScaleT = typename MajorScale<note_c_t<rootNote>>::type;


#endif //ROCKY_MUSE_MUSICALSCALE_H

