#include "../include/deleterec.h"

/**
 * Delete record recRid from relation relNum
 *
 * @param relNum - the relation number
 * @param rid    - Rid of record to be deleted
 * @return OK - everything goes well
 *         NOTOK - otherwise
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_Buffer[relNum]
 *      g_CatCache[relNum]
 *
 * ERRORS REPORTED:
 *      NULL_ARGUMENT_RECEIVED
 *      RELNUM_OUT_OF_BOUND
 *      (highly doubt if these will ever come into play)
 *
 * ALGORITHM:
 *      1. Check for errors
 *      2. Read the page containing rid
 *      3. Update the slotmap and numRecs
 *      4. Set the buffer and cache to dirty
 *
 * IMPLEMENTATION NOTES:
 *      Uses ReadPage()
 */
int DeleteRec(const int relNum, const Rid *rid) {
    if (rid == NULL) {
        return ErrorMsgs(NULL_ARGUMENT_RECEIVED, g_PrintFlag);
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        return ErrorMsgs(RELNUM_OUT_OF_BOUND, g_PrintFlag);
    }

    if (ReadPage(relNum, rid->pid) == OK) {
        g_Buffer[relNum].page.slotmap &= ~(1 << (32 - rid->slotnum));
        g_Buffer[relNum].dirty = TRUE;
        g_CatCache[relNum].numRecs--;
        g_CatCache[relNum].dirty = TRUE;
        return OK;
    } else {
        return NOTOK;
    }
}
