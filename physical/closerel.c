/*
 * closerel.c
 *
 *  Created on: 31-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/closerel.h"

/*
 * Function: CloseRel() 
 * ----------------------
 * Close the relation identified by relNum after writing to disk any changes in its buffer page or 
 * in its cached catalog information
 *
 *  relNum : relation number
 *
 *  returns: OK on success
 *           NOTOK on failure
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_CatCache[relNum].dirty = FALSE
 *      g_CacheInUse[relNum] = FALSE;
 *      g_CacheTimestamp[relNum] = 0;
 *
 * ERRORS REPORTED:
 *      RELNOEXIST
 *
 * ALGORITHM:
 *   1. Checks for errors.
 *   2. FlushPage current bufferpage, which will update disk if buffer is dirty
 *   3. checks if cache entry is dirty
 *   4. if yes, update relcat entries for corresponding entry.
 *
 * IMPLEMENTATION NOTES:
 *      Uses FlushPage, FindRec, WriteRec from physical layer.
 */

int CloseRel(int relNum) {
    int numPgs, numRecs;
    char *recPtr;
    Rid startRid = { 1, 0 }, *foundRid;

    FlushPage(relNum);

    if (g_CatCache[relNum].dirty == FALSE)
        return OK;
    else {
        if (FindRec(RELCAT_CACHE, &startRid, &foundRid, &recPtr, STRING, RELNAME, 0,
                g_CatCache[relNum].relName, EQ) == NOTOK) {
            return ErrorMsgs(RELNOEXIST, g_PrintFlag);
        } else {
            numPgs = g_CatCache[relNum].numPgs;
            numRecs = g_CatCache[relNum].numRecs;
            convertIntToByteArray(numRecs, recPtr + 32);
            convertIntToByteArray(numPgs, recPtr + 36);

            WriteRec(RELCAT_CACHE, recPtr, foundRid);
            FlushPage(RELCAT_CACHE);

            struct attrCatalog *temp, *attrListHead = g_CatCache[relNum].attrList;
            g_CatCache[relNum].dirty = FALSE;
            g_CacheInUse[relNum] = FALSE;
            close(g_CatCache[relNum].relFile);

            temp = attrListHead;
            while (temp != NULL) {
                attrListHead = temp->next;
                free(temp);
                temp = attrListHead;
            }
        }
    }
    return OK;
}
