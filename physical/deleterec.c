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
        ErrorMsgs(NULL_ARGUMENT_RECEIVED);
        return NOTOK;
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        ErrorMsgs(RELNUM_OUT_OF_BOUND);
        return NOTOK;
    }

    if (ReadPage(relNum, rid->pid) == OK) {
        g_buffer[relNum].page.slotmap &= ~(1 << rid->slotnum);
        g_buffer[relNum].dirty = TRUE;
        g_catcache[relNum].numRecs--;
        return OK;
    } else {
        return NOTOK;
    }
}
