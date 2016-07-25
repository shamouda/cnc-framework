/**********************************************\
 *  WARNING: AUTO-GENERATED FILE!             *
 *  This file WILL BE OVERWRITTEN on each     *
 *  invocation of the graph translator tool.  *
\**********************************************/

#include "cncocr_internal.h"

/* The structure to hold an item in the item collection */
typedef struct _cncItemCollEntry {
    ocrGuid_t event; /* The event representing the data item. Data will be put through the event when it is satisfied */
    struct _cncItemCollEntry * volatile nxt; /* The next bucket in the hashtable */
    char creator; /* Who created this entry (could be from a Put or a Get)*/
    cncTag_t tag[]; /* Tags are byte arrays, with a known length for each item collection */
} _cncItemCollectionEntry;

/* Get an entry from the item collection, or create and insert one (atomically) if it doesn't exist.
 * The creator parameter PUTTER/GETTER role ensures that multiple puts are not allowed.
 */
static bool _allocateEntryIfAbsent(
        _cncItemCollectionEntry * volatile * hashmap, cncTag_t *tag,
        int length, char creator, _cncItemCollectionEntry **entryOut) {
    const int tagByteCount = length*sizeof(*tag);
    int index = (_cncTagHash(tag, length)) % CNC_TABLE_SIZE;
    _cncItemCollectionEntry * volatile current = hashmap[index];
    _cncItemCollectionEntry * volatile * currentLocation = &hashmap[index];
    _cncItemCollectionEntry * volatile head = current;
    _cncItemCollectionEntry * volatile tail = NULL;

    _cncItemCollectionEntry * entry = NULL;

    while (1) {
        /* traverse the buckets in the table to get to the last one */
        while (current != tail) {
            if (_cncTagEquals(current->tag, tag, length)) {
                /* deallocate the entry we eagerly allocated in a previous iteration of the outer while(1) loop */
                if (entry != NULL){
                    ocrEventDestroy(entry->event);
                    free(entry);
                }

                /* just return the table entry if it already has the tag */
                *entryOut = current;
                return false;
            }
            current = current->nxt;
        }

        /* allocate a new entry if this is the first time we are going to try and insert a new entry to the end of the bucket list */
        if (entry == NULL) {
            entry = malloc(sizeof(_cncItemCollectionEntry)+tagByteCount);
            entry->creator = creator;
            memcpy(entry->tag, tag, tagByteCount);
            ocrEventCreate(&(entry->event), OCR_EVENT_IDEM_T, true);
        }
        entry->nxt=head;

        /* try to insert the new entry into the _first_ position in a bucket of the table */
        if (__sync_bool_compare_and_swap(currentLocation, head, entry)) {
            *entryOut = entry;
            return true;
        }

        /* CAS failed, which means that someone else inserted the new entry into the table while we were trying to do so, we need to try again */
        current = hashmap[index]; //do not update tail anymore if deletes are inserted.
        tail = head;
        head = current;
    }

    ASSERT(!"Unreachable"); /* we should never get here */
    return false;
}

static inline ocrGuid_t _cncItemCollUpdateLocal(_cncItemCollectionEntry **coll, cncTag_t *tag, u32 tagLength, u8 role,
        ocrGuid_t input, u32 slot, ocrDbAccessMode_t mode) {
    // local hashtable update
    _cncItemCollectionEntry *entry;
    bool wasUpdated = _allocateEntryIfAbsent(coll, tag, tagLength, role, &entry);
    if (role == _CNC_PUTTER_ROLE) { // put input into collection
        ocrEventSatisfy(entry->event, input);
    }
    else { // get placeholder and pass to input
        ocrAddDependence(entry->event, input, slot, mode);
    }
    // Notify caller if the entry was already there
    return wasUpdated ? entry->event : NULL_GUID;
}

cncItemCollection_t _cncItemCollectionCreate(void) {
    return calloc(CNC_TABLE_SIZE, sizeof(struct _cncItemCollEntry*));
}

void _cncItemCollectionDestroy(cncItemCollection_t coll) {
    // FIXME - need to do a deep traversal to really destroy the collection
    free(coll);
}

cncItemCollection_t _cncItemCollectionSingletonCreate(void) {
    return calloc(1, sizeof(struct _cncItemCollEntry*));
}

void _cncItemCollectionSingletonDestroy(cncItemCollection_t coll) {
    // FIXME - need to do a deep traversal to really destroy the collection
    free(coll);
}

struct _cncItemCollUpdateParams {
    ocrGuid_t input;
    ptrdiff_t collOffset;
    u8 role;
    u32 tagLength;
    u32 slot;
    ocrDbAccessMode_t mode;
    cncTag_t tag[];
};

static ocrGuid_t _cncItemCollUpdateEdt(u32 paramc, u64 paramv[], u32 depc, ocrEdtDep_t depv[]) {
    struct _cncItemCollUpdateParams *p = depv[0].ptr;
    u8 *ctxBase = depv[1].ptr;
    cncItemCollection_t *coll = (void*)(ctxBase + p->collOffset);
    ocrGuid_t result = _cncItemCollUpdateLocal(*coll, p->tag, p->tagLength, p->role, p->input, p->slot, p->mode);
    ocrDbDestroy(depv[0].guid);
    return result;
}

void _cncItemCollUpdate(cncItemCollHandle_t handle, cncTag_t *tag, u32 tagLength, u8 role,
        ocrGuid_t input, u32 slot, ocrDbAccessMode_t mode) {
    ocrGuid_t pGuid;
    struct _cncItemCollUpdateParams *p;
    const ocrGuid_t remoteCtx = handle.remoteCtxGuid;
    const ocrGuid_t affinity = _cncAffinityFromCtx(remoteCtx);
    const bool isLocalOp = ocrGuidIsEq(affinity, _cncCurrentAffinity());
    // Handle local operations
    if (isLocalOp) {
        _cncItemCollUpdateLocal(handle.coll, tag, tagLength, role, input, slot, mode);
        return;
    }
    if (role == _CNC_GETTER_ROLE) {
        // Remote lookup for gets only if local get failed
        ocrGuid_t placeholder = _cncItemCollUpdateLocal(handle.coll, tag, tagLength, role, input, slot, mode);
        if (ocrGuidIsNull(placeholder)) { return; } // already registered on remote
        input = placeholder;
        slot = 0;
    }
    // Handle remote operations
    { // init params struct
        const size_t tagBytes = tagLength*sizeof(*tag);
        _CNC_DBCREATE(&pGuid, (void**)&p, sizeof(*p) + tagBytes);
        p->input = input;
        p->collOffset = handle.collOffset;
        p->role = role;
        p->tagLength = tagLength;
        p->slot = slot;
        p->mode = mode;
        memcpy(p->tag, tag, tagBytes);
    }
    { // do remote op
        ocrGuid_t tmpl, edt;
        // FIXME - should just set up this template somewhere once...
        ocrEdtTemplateCreate(&tmpl, _cncItemCollUpdateEdt, 0, 2);
        ocrHint_t hint;
        ocrEdtCreate(&edt, tmpl,
                /*paramc=*/0, /*paramv=*/NULL,
                /*depc=*/EDT_PARAM_DEF, /*depv=*/NULL,
                /*properties=*/EDT_PROP_NONE,
                /*hint=*/_cncEdtAffinityHint(&hint, affinity),
                /*outEvent=*/NULL);
        ocrAddDependence(pGuid, edt, 0, DB_MODE_RO);
        ocrAddEventSatisfier(edt, pGuid, (u64)11);
        ocrAddDependence(remoteCtx, edt, 1, DB_MODE_RO);
        ocrAddEventSatisfier(edt, remoteCtx, (u64)12);
        ocrEdtTemplateDestroy(tmpl);
    }
}
