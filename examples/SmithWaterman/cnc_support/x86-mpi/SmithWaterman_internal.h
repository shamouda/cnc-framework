/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#ifndef _CNCOCR_SMITHWATERMAN_INTERNAL_H_
#define _CNCOCR_SMITHWATERMAN_INTERNAL_H_

#include "SmithWaterman.h"
#include "cncocr_internal.h"

/********************************\
 ******** ITEM FUNCTIONS ********
\********************************/


void cncGet_above(cncTag_t i, cncTag_t j, ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, SmithWatermanCtx *ctx);

void cncGet_left(cncTag_t i, cncTag_t j, ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, SmithWatermanCtx *ctx);

void cncGet_data(ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, SmithWatermanCtx *ctx);

void cncGet_startTime(ocrGuid_t destination, u32 slot, ocrDbAccessMode_t mode, SmithWatermanCtx *ctx);


#ifdef CNC_AFFINITIES
static inline cncLocation_t _cncItemDistFn_above(cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx) { return j % ctx->_affinityCount; }
static inline cncLocation_t _cncItemDistFn_left(cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx) { return j % ctx->_affinityCount; }
static inline cncLocation_t _cncItemDistFn_data(SmithWatermanCtx *ctx) { return 2 % ctx->_affinityCount; }
static inline cncLocation_t _cncItemDistFn_startTime(SmithWatermanCtx *ctx) { return 3 % ctx->_affinityCount; }
#endif /* CNC_AFFINITIES */

/********************************\
 ******** STEP FUNCTIONS ********
\********************************/

void SmithWaterman_cncInitialize(SmithWatermanArgs *args, SmithWatermanCtx *ctx);

void SmithWaterman_cncFinalize(struct timeval *startTime, int *above, SmithWatermanCtx *ctx);
ocrGuid_t _SmithWaterman_cncStep_cncFinalize(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]);

void SmithWaterman_swStep(cncTag_t i, cncTag_t j, SeqData *data, int *above, int *left, SmithWatermanCtx *ctx);
ocrGuid_t _SmithWaterman_cncStep_swStep(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]);

#endif /*_CNCOCR_SMITHWATERMAN_INTERNAL_H_*/
