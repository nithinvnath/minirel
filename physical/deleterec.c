#include "../include/deleterec.h"

/**
 * Delete record recRid from relation relNum
 *
 * @param relNum
 * @param rid
 * @return OK or NOTOK
 */
int DeleteRec(const int relNum, const Rid *rid) {
    if (rid == NULL) {
        return ErrorMsgs(NULL_ARGUMENT_RECEIVED,g_PrintFlag);
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        return ErrorMsgs(RELNUM_OUT_OF_BOUND,g_PrintFlag);
    }

    if (ReadPage(relNum, rid->pid) == OK) {
        g_Buffer[relNum].page.slotmap &= ~(1 << (32-rid->slotnum));
        g_Buffer[relNum].dirty = TRUE;
        g_CatCache[relNum].numRecs--;
        g_CatCache[relNum].dirty = TRUE;
        return OK;
    } else {
        return NOTOK;
    }
}
