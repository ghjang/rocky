#ifndef ROCKY_MUSE_MUSICALSCALE_H
#define ROCKY_MUSE_MUSICALSCALE_H


#include "rocky/base/TypeComposition.h"
#include "rocky/skull/Map.h"
#include "rocky/wolca/NestList.h"
#include "rocky/app/Rotate.h"
#include "rocky/app/Extract.h"
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


#endif //ROCKY_MUSE_MUSICALSCALE_H

