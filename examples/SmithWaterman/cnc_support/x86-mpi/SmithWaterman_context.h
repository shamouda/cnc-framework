/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#ifndef _CNC_SMITHWATERMAN_CONTEXT_H_
#define _CNC_SMITHWATERMAN_CONTEXT_H_

#include "cncocr.h"
#include "SmithWaterman_defs.h"

typedef struct SmithWatermanContext {
    int tw, th;
    int ntw, nth;
    struct {
        ocrGuid_t self;
        ocrGuid_t finalizedEvent;
        ocrGuid_t quiescedEvent;
        ocrGuid_t doneEvent;
        ocrGuid_t awaitTag;
        ocrGuid_t contextReady;
    } _guids;
    struct {
        cncItemCollection_t above;
        cncItemCollection_t left;
        cncItemCollection_t data;
        cncItemCollection_t startTime;
    } _items;
    struct {
        ocrGuid_t cncFinalize;
        ocrGuid_t swStep;
    } _steps;
#ifdef CNC_AFFINITIES
    cncLocation_t _rank;
    u64 _affinityCount;
    ocrGuid_t _affinities[];
#endif /* CNC_AFFINITIES */
} SmithWatermanCtx;

#endif /*_CNC_SMITHWATERMAN_CONTEXT_H_*/
