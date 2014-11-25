#include "../include/writerec.h"

/**
 * Make the record-sized byte array pointed at by recPtr to be the new contents of record
 * recRid in relation relNum
 *
 * @param relNum
 * @param recPtr
 * @param RecId
 * @return OK or NOTOK
 * @author nithin
 *
 * GLOBAL VARIABLES MODIFIED
 *      g_Buffer[relNum]
 *
 * ERRORS REPORTED:
 *      NULL_ARGUMENT_RECEIVED
 *      RELNUM_OUT_OF_BOUND
 *
 * ALGORITHM:
 *      1. Check for errors in received arguments
 *      2. Read the page given by recId using ReadPage()
 *      3. Iterate over each character of recPtr
 *      4.      Assign recPtr[i] to page.contents[i+offset]
 *      5. Set the buffer as dirty
 *
 * IMPLEMENTATION NOTES:
 *      We use a for loop to copy the char array instead of strcpy as
 *      the array may contain null character which we need to get copied
 *
 *      Uses ReadPage()
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
