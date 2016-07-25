/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#ifndef _CNC_SMITHWATERMAN_H_
#define _CNC_SMITHWATERMAN_H_
#include "SmithWaterman_context.h"
#include "cnc_common.h"

/***************************\
 ******** CNC GRAPH ********
\***************************/

SmithWatermanCtx *SmithWaterman_create(void);
void SmithWaterman_destroy(SmithWatermanCtx *ctx);

void SmithWaterman_launch(SmithWatermanArgs *args, SmithWatermanCtx *ctx);
void SmithWaterman_await(SmithWatermanCtx *ctx);

/**********************************\
 ******** ITEM KEY STRUCTS ********
\**********************************/

typedef struct { cncTag_t i, j; } aboveItemKey;
typedef struct { cncTag_t i, j; } leftItemKey;

/**************************\
 ******** ITEM PUT ********
\**************************/

// above

void cncPut_above(int *_item, cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx);

// left

void cncPut_left(int *_item, cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx);

// data

void cncPut_data(SeqData *_item, SmithWatermanCtx *ctx);

// startTime

void cncPut_startTime(struct timeval *_item, SmithWatermanCtx *ctx);

/************************************\
 ******** STEP PRESCRIPTIONS ********
\************************************/

void cncPrescribe_cncFinalize(SmithWatermanCtx *ctx);
void cncPrescribe_swStep(cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx);


#endif /*_CNC_SMITHWATERMAN_H_*/
