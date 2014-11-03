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
        return ErrorMsgs(NULL_ARGUMENT_RECEIVED,g_print_flag);
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        return ErrorMsgs(RELNUM_OUT_OF_BOUND,g_print_flag);
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
