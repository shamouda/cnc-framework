/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#include "SmithWaterman_internal.h"

#ifdef CNC_DEBUG_LOG
#if !defined(CNCOCR_x86)
#error "Debug logging mode only supported on x86 targets"
#endif
#include <pthread.h>
extern pthread_mutex_t _cncDebugMutex;
#endif /* CNC_DEBUG_LOG */


/* cncFinalize setup/teardown function */
ocrGuid_t _SmithWaterman_cncStep_cncFinalize(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    SmithWatermanCtx *ctx = depv[0].ptr;

    u64 *_tag = paramv; MAYBE_UNUSED(_tag);

    s32 _edtSlot = 1; MAYBE_UNUSED(_edtSlot);

    struct timeval *startTime;
    startTime = (struct timeval *)_cncItemDataPtr(depv[_edtSlot++].ptr);

    int *above;
    above = (int *)_cncItemDataPtr(depv[_edtSlot++].ptr);

    #ifdef CNC_DEBUG_LOG
        pthread_mutex_lock(&_cncDebugMutex);
    #endif
    // Call user-defined step function
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "RUNNING cncFinalize @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: RUNNING cncFinalize @ 0\n");
    #endif
    SmithWaterman_cncFinalize(startTime, above, ctx);
    // Clean up
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "DONE cncFinalize @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: DONE cncFinalize @ 0\n");
    #endif
    #ifdef CNC_DEBUG_LOG
        pthread_mutex_unlock(&_cncDebugMutex);
    #endif
    return NULL_GUID;
}

/* cncFinalize task creation */
static void cncPrescribeInternal_cncFinalize(u64 *_tag, SmithWatermanCtx *ctx) {
    ocrGuid_t _stepGuid;
    u64 _depc = 1 + 1 + 1;
    ocrHint_t _hint;
    ocrHint_t *const _hintPtr = _cncCurrentEdtAffinityHint(&_hint);
    ocrEdtCreate(&_stepGuid, ctx->_steps.cncFinalize,
        /*paramc=*/0, /*paramv=*/_tag,
        /*depc=*/_depc, /*depv=*/NULL,
        /*properties=*/EDT_PROP_NONE,
        /*hint=*/_hintPtr, /*outEvent=*/NULL);

    s32 _edtSlot = 0; MAYBE_UNUSED(_edtSlot);
    ocrAddDependence(ctx->_guids.self, _stepGuid, _edtSlot++, _CNC_AUX_DATA_MODE);


    { // Set up "startTime" input dependencies
        cncGet_startTime(_stepGuid, _edtSlot++, _CNC_ITEM_GET_MODE, ctx);
    }

    { // Set up "above" input dependencies
        s64 _i0 = ctx->nth;
        s64 _i1 = ctx->ntw-1;
        cncGet_above(_i0, _i1, _stepGuid, _edtSlot++, _CNC_ITEM_GET_MODE, ctx);
    }

    ASSERT(_depc == _edtSlot);
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PRESCRIBED cncFinalize @ 0\n");
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PRESCRIBED cncFinalize @ 0\n");
    #endif
}

#ifdef CNC_AFFINITIES
static ocrGuid_t _cncRemotePrescribe_cncFinalize(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    SmithWatermanCtx *ctx = depv[0].ptr;

    cncPrescribeInternal_cncFinalize(paramv, ctx);

    return NULL_GUID;
}
#endif /* CNC_AFFINITIES */

/* cncFinalize task creation */
void cncPrescribe_cncFinalize(SmithWatermanCtx *ctx) {
    u64 *_args = NULL;
    // affinity
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = 2 % ctx->_affinityCount;
    if (_loc != ctx->_rank) {
        const ocrGuid_t _remoteCtx = ctx->_affinities[_loc];
        const ocrGuid_t _affinity = _cncAffinityFromCtx(_remoteCtx);
        const u32 _argCount = 0;
        const u32 _depCount = 1;
        ocrGuid_t _deps[] = { _remoteCtx };
        // XXX - should just create this template along with the step function template
        ocrGuid_t edtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _cncRemotePrescribe_cncFinalize, _argCount, _depCount);
        ocrHint_t _hint;
        ocrEdtCreate(&edtGuid, templGuid,
                /*paramc=*/_argCount, /*paramv=*/_args,
                /*depc=*/_depCount, /*depv=*/_deps,
                /*properties=*/EDT_PROP_NONE,
                /*hint=*/_cncEdtAffinityHint(&_hint, _affinity),
                /*outEvent=*/NULL);
        ocrEdtTemplateDestroy(templGuid);
        return;
    }
    #endif /* CNC_AFFINITIES */
    cncPrescribeInternal_cncFinalize(_args, ctx);
}

/* swStep setup/teardown function */
ocrGuid_t _SmithWaterman_cncStep_swStep(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    SmithWatermanCtx *ctx = depv[0].ptr;

    u64 *_tag = paramv; MAYBE_UNUSED(_tag);
    const cncTag_t i = (cncTag_t)_tag[0]; MAYBE_UNUSED(i);
    const cncTag_t j = (cncTag_t)_tag[1]; MAYBE_UNUSED(j);

    s32 _edtSlot = 1; MAYBE_UNUSED(_edtSlot);

    SeqData *data;
    data = (SeqData *)_cncItemDataPtr(depv[_edtSlot++].ptr);

    int *above;
    above = (int *)_cncItemDataPtr(depv[_edtSlot++].ptr);

    int *left;
    left = (int *)_cncItemDataPtr(depv[_edtSlot++].ptr);

    #ifdef CNC_DEBUG_LOG
        pthread_mutex_lock(&_cncDebugMutex);
    #endif
    // Call user-defined step function
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "RUNNING swStep @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: RUNNING swStep @ %ld, %ld\n", i, j);
    #endif
    SmithWaterman_swStep(i, j, data, above, left, ctx);
    // Clean up
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "DONE swStep @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: DONE swStep @ %ld, %ld\n", i, j);
    #endif
    #ifdef CNC_DEBUG_LOG
        pthread_mutex_unlock(&_cncDebugMutex);
    #endif
    return NULL_GUID;
}

/* swStep task creation */
static void cncPrescribeInternal_swStep(u64 *_tag, SmithWatermanCtx *ctx) {
    const cncTag_t i = (cncTag_t)_tag[0]; MAYBE_UNUSED(i);
    const cncTag_t j = (cncTag_t)_tag[1]; MAYBE_UNUSED(j);
    ocrGuid_t _stepGuid;
    u64 _depc = 1 + 1 + 1 + 1;
    ocrHint_t _hint;
    ocrHint_t *const _hintPtr = _cncCurrentEdtAffinityHint(&_hint);
    ocrEdtCreate(&_stepGuid, ctx->_steps.swStep,
        /*paramc=*/2, /*paramv=*/_tag,
        /*depc=*/_depc, /*depv=*/NULL,
        /*properties=*/EDT_PROP_NONE,
        /*hint=*/_hintPtr, /*outEvent=*/NULL);

    s32 _edtSlot = 0; MAYBE_UNUSED(_edtSlot);
    ocrAddDependence(ctx->_guids.self, _stepGuid, _edtSlot++, _CNC_AUX_DATA_MODE);


    { // Set up "data" input dependencies
        cncGet_data(_stepGuid, _edtSlot++, _CNC_ITEM_GET_MODE, ctx);
    }
    if (i > 0) {
        { // Set up "above" input dependencies
            s64 _i0 = i;
            s64 _i1 = j;
            cncGet_above(_i0, _i1, _stepGuid, _edtSlot++, _CNC_ITEM_GET_MODE, ctx);
        }
    }
    else {
        { // Set up "above" input dependencies
            ocrAddDependence(NULL_GUID, _stepGuid, _edtSlot++, DB_MODE_NULL);
        }
    }

    if (j > 0) {
        { // Set up "left" input dependencies
            s64 _i0 = i;
            s64 _i1 = j;
            cncGet_left(_i0, _i1, _stepGuid, _edtSlot++, _CNC_ITEM_GET_MODE, ctx);
        }
    }
    else {
        { // Set up "left" input dependencies
            ocrAddDependence(NULL_GUID, _stepGuid, _edtSlot++, DB_MODE_NULL);
        }
    }


    ASSERT(_depc == _edtSlot);
    #ifdef CNC_DEBUG_LOG
        fprintf(cncDebugLog, "PRESCRIBED swStep @ %ld, %ld\n", i, j);
        fflush(cncDebugLog);
    #elif CNC_DEBUG_TRACE
        printf("<<CnC Trace>>: PRESCRIBED swStep @ %ld, %ld\n", i, j);
    #endif
}

#ifdef CNC_AFFINITIES
static ocrGuid_t _cncRemotePrescribe_swStep(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    SmithWatermanCtx *ctx = depv[0].ptr;

    cncPrescribeInternal_swStep(paramv, ctx);

    return NULL_GUID;
}
#endif /* CNC_AFFINITIES */

/* swStep task creation */
void cncPrescribe_swStep(cncTag_t i, cncTag_t j, SmithWatermanCtx *ctx) {
    u64 _args[] = { (u64)i, (u64)j };
    // affinity
    #ifdef CNC_AFFINITIES
    const cncLocation_t _loc = j % ctx->_affinityCount;
    if (_loc != ctx->_rank) {
        const ocrGuid_t _remoteCtx = ctx->_affinities[_loc];
        const ocrGuid_t _affinity = _cncAffinityFromCtx(_remoteCtx);
        const u32 _argCount = 2;
        const u32 _depCount = 1;
        ocrGuid_t _deps[] = { _remoteCtx };
        // XXX - should just create this template along with the step function template
        ocrGuid_t edtGuid, templGuid;
        ocrEdtTemplateCreate(&templGuid, _cncRemotePrescribe_swStep, _argCount, _depCount);
        ocrHint_t _hint;
        ocrEdtCreate(&edtGuid, templGuid,
                /*paramc=*/_argCount, /*paramv=*/_args,
                /*depc=*/_depCount, /*depv=*/_deps,
                /*properties=*/EDT_PROP_NONE,
                /*hint=*/_cncEdtAffinityHint(&_hint, _affinity),
                /*outEvent=*/NULL);
        ocrEdtTemplateDestroy(templGuid);
        return;
    }
    #endif /* CNC_AFFINITIES */
    cncPrescribeInternal_swStep(_args, ctx);
}


