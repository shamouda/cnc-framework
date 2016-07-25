/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#include "SmithWaterman_internal.h"
#include <string.h>


/* above */

void cncPut_above(int *_item, cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx) {
    ocrGuid_t _handle = _cncItemGuid(_item);
    // MUST release first to conform with OCR memory model
    // otherwise the item data might not be visible to other EDTs
    if (!_cncItemGetReleasedFlag(_item)) {
        _cncItemToggleReleasedFlag(_item);
        ocrDbRelease(_handle);
    }
    #ifdef CNC_AFFINITIES
    // FIXME - Need to copy to remote node if the affinity doesn't match
    const cncLocation_t _loc = _cncItemDistFn_above(i, j, ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PUT above @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PUT above @ %ld, %ld\n", i, j);
    #endif
    cncTag_t _tag[] = { i, j };
    const size_t _tagSize = sizeof(_tag)/sizeof(*_tag);
    _cncPut(_handle, _tag, _tagSize, _CNC_ITEM_COLL_HANDLE(ctx, above, _loc));
}

void cncGet_above(cncTag_t i, cncTag_t j, ocrGuid_t _destination, u32 _slot, ocrDbAccessMode_t _mode, SmithWatermanCtx *ctx) {
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "GET-DEP above @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: GET-DEP above @ %ld, %ld\n", i, j);
    #endif
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = _cncItemDistFn_above(i, j, ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    cncTag_t _tag[] = { i, j };
    const size_t _tagSize = sizeof(_tag)/sizeof(*_tag);
    return _cncGet(_tag, _tagSize, _destination, _slot, _mode, _CNC_ITEM_COLL_HANDLE(ctx, above, _loc));
}


/* left */

void cncPut_left(int *_item, cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx) {
    ocrGuid_t _handle = _cncItemGuid(_item);
    // MUST release first to conform with OCR memory model
    // otherwise the item data might not be visible to other EDTs
    if (!_cncItemGetReleasedFlag(_item)) {
        _cncItemToggleReleasedFlag(_item);
        ocrDbRelease(_handle);
    }
    #ifdef CNC_AFFINITIES
    // FIXME - Need to copy to remote node if the affinity doesn't match
    const cncLocation_t _loc = _cncItemDistFn_left(i, j, ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PUT left @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PUT left @ %ld, %ld\n", i, j);
    #endif
    cncTag_t _tag[] = { i, j };
    const size_t _tagSize = sizeof(_tag)/sizeof(*_tag);
    _cncPut(_handle, _tag, _tagSize, _CNC_ITEM_COLL_HANDLE(ctx, left, _loc));
}

void cncGet_left(cncTag_t i, cncTag_t j, ocrGuid_t _destination, u32 _slot, ocrDbAccessMode_t _mode, SmithWatermanCtx *ctx) {
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "GET-DEP left @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: GET-DEP left @ %ld, %ld\n", i, j);
    #endif
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = _cncItemDistFn_left(i, j, ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    cncTag_t _tag[] = { i, j };
    const size_t _tagSize = sizeof(_tag)/sizeof(*_tag);
    return _cncGet(_tag, _tagSize, _destination, _slot, _mode, _CNC_ITEM_COLL_HANDLE(ctx, left, _loc));
}


/* data */

void cncPut_data(SeqData *_item, SmithWatermanCtx *ctx) {
    ocrGuid_t _handle = _cncItemGuid(_item);
    // MUST release first to conform with OCR memory model
    // otherwise the item data might not be visible to other EDTs
    if (!_cncItemGetReleasedFlag(_item)) {
        _cncItemToggleReleasedFlag(_item);
        ocrDbRelease(_handle);
    }
    #ifdef CNC_AFFINITIES
    // FIXME - Need to copy to remote node if the affinity doesn't match
    const cncLocation_t _loc = _cncItemDistFn_data(ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PUT data @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PUT data @ 0\n");
    #endif
    _cncPutSingleton(_handle, _CNC_ITEM_COLL_HANDLE(ctx, data, _loc));
}

void cncGet_data(ocrGuid_t _destination, u32 _slot, ocrDbAccessMode_t _mode, SmithWatermanCtx *ctx) {
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "GET-DEP data @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: GET-DEP data @ 0\n");
    #endif
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = _cncItemDistFn_data(ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    return _cncGetSingleton(_destination, _slot, _mode, _CNC_ITEM_COLL_HANDLE(ctx, data, _loc));
}


/* startTime */

void cncPut_startTime(struct timeval *_item, SmithWatermanCtx *ctx) {
    ocrGuid_t _handle = _cncItemGuid(_item);
    // MUST release first to conform with OCR memory model
    // otherwise the item data might not be visible to other EDTs
    if (!_cncItemGetReleasedFlag(_item)) {
        _cncItemToggleReleasedFlag(_item);
        ocrDbRelease(_handle);
    }
    #ifdef CNC_AFFINITIES
    // FIXME - Need to copy to remote node if the affinity doesn't match
    const cncLocation_t _loc = _cncItemDistFn_startTime(ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PUT startTime @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PUT startTime @ 0\n");
    #endif
    _cncPutSingleton(_handle, _CNC_ITEM_COLL_HANDLE(ctx, startTime, _loc));
}

void cncGet_startTime(ocrGuid_t _destination, u32 _slot, ocrDbAccessMode_t _mode, SmithWatermanCtx *ctx) {
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "GET-DEP startTime @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: GET-DEP startTime @ 0\n");
    #endif
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = _cncItemDistFn_startTime(ctx);
    #else
    const cncLocation_t _loc = CNC_CURRENT_LOCATION; MAYBE_UNUSED(_loc);
    #endif /* CNC_AFFINITIES */
    return _cncGetSingleton(_destination, _slot, _mode, _CNC_ITEM_COLL_HANDLE(ctx, startTime, _loc));
}


