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
int WriteRec(const int relNum, const char *recPtr, const Rid *recId) {
    if (recPtr == NULL || recId == NULL) {
        ErrorMsgs(NULL_ARGUMENT_RECEIVED, g_PrintFlag);
    }
    if (relNum < 0 || relNum > MAXOPEN) {
        ErrorMsgs(RELNUM_OUT_OF_BOUND, g_PrintFlag);
    }
    /*  Write the contents  */
    ReadPage(relNum, recId->pid);
    int recLength = g_CatCache[relNum].recLength;
    int offset = (recId->slotnum - 1) * recLength;
    int i, j;
    for (i = offset, j = 0; j < recLength; ++i, j++) {
        g_Buffer[relNum].page.contents[i] = recPtr[j];
    }

    g_Buffer[relNum].dirty = TRUE;

    return OK;
}
