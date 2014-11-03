#include "../include/writerec.h"

/**
 * Make the record-sized byte array pointed at by recPtr to be the new contents of record
 * recRid in relation relNum
 *
 * @param relNum
 * @param recPtr
 * @param RecId
 * @return OK or NOTOK
 */
int WriteRec(const int relNum, const char *recPtr, const Rid *RecId) {
    if (recPtr == NULL || RecId == NULL) {
        ErrorMsgs(NULL_ARGUMENT_RECEIVED, g_print_flag);
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        ErrorMsgs(RELNUM_OUT_OF_BOUND, g_print_flag);
    }
    /*  Write the contents  */
    ReadPage(relNum, RecId->pid);
    int recLength = g_catcache[relNum].recLength;
    int offset = (RecId->slotnum - 1) * recLength;
    int i, j;
    for (i = offset, j = 0; j < recLength; ++i, j++) {
        g_buffer[relNum].page.contents[i] = recPtr[j];
    }

    g_buffer[relNum].dirty = TRUE;

    return OK;
}
