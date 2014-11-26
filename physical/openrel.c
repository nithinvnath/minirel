/*
 * openrel.c
 *
 *  Created on: 28-Oct-2014
 *      Author: Dheeraj
 */

#include "../include/openrel.h"

/*
 * Function:  OpenRel 
 * ----------------------
 * Open relation 'relName' and return its relation number.
 *
 *  RelName: name of the relation
 *  
 *  returns: RelNum
 *           NOTOK on failure
 *
 * GLOBAL VARIABLES MODIFIED:
 *      g_CacheInUse[i] changes to TRUE to the slot which is opened for new relation
 *      g_CacheTimestamp[i] updates to latest timestamp
 *      g_CacheLastTimestamp updated
 *
 *      g_CatCache[i] entries are updated w.r.t. new relation opened.
 *
 * ERRORS REPORTED:
 *      RELNOEXIST
 *      NO_ATTRS_FOUND
 *
 * ALGORITHM:
 *    1. Finds an empty slot if available.
 *    2. Else closes an opened relation using FIFO approach.
 *    3. Updates the catcache entries to new slot.
 *    4. Creates cache values of attribute catalog.
 *
 * IMPLEMENTATION NOTES:
 *      Uses FindRec, CloseRel from physical layer
 */

int OpenRel(char* relName) {
    Rid startRid, *foundRid;
    char* byteArray;
    struct attrCatalog *temp = NULL, *newNode = NULL;
    bool isFirstExecution = TRUE;
    int i, j, returnVal;
    for (i = 0; i < MAXOPEN; i++) {
        if (g_CacheInUse[i] == TRUE && strcmp(g_CatCache[i].relName, relName) == 0) {

            g_CacheTimestamp[i] = g_CacheLastTimestamp;
            g_CacheLastTimestamp++;
            return i;
        }
    }

    startRid.pid = 1;
    startRid.slotnum = 0;

    returnVal = FindRec(RELCAT_CACHE, &startRid, &foundRid, &byteArray, 's', RELNAME, 0, relName,
    EQ);

    if (returnVal == NOTOK) {
        return ErrorMsgs(RELNOEXIST, g_PrintFlag);
    }/* Relation does not exist with given Relation Name */
    else {
        /* -------Cache Management----------- 
         take out first cache position which is empty ( or choose one to replace )
         fill out entries and return RelNum */

        for (i = 2; i < MAXOPEN; i++) {
            if (g_CacheInUse[i] == FALSE)
                break;
        }

        if (i != MAXOPEN) { /* Found an empty slot.*/
            g_CacheInUse[i] = TRUE;
            g_CacheTimestamp[i] = g_CacheLastTimestamp;
            g_CacheLastTimestamp++;

        } else { /* Replace an existing cat_cache entry*/

            int minTimestamp = g_CacheTimestamp[2];
            int indexMinTimestamp = 2;

            for (i = 2; i < MAXOPEN; i++) {
                if (g_CacheTimestamp[i] < minTimestamp) {
                    minTimestamp = g_CacheTimestamp[i];
                    indexMinTimestamp = i;
                }
            }
            i = indexMinTimestamp;

            /* update numRecs, numPgs in RelCat relation from g_CatCache[i] entry (if modified), and
             free the cache entry as well as buffer slot  */
            CloseRel(i);

            g_CacheTimestamp[i] = g_CacheLastTimestamp;
            g_CacheInUse[i] = TRUE;
            g_CacheLastTimestamp++;
        }

        /* position i is available */
        strcpy(g_CatCache[i].relName, relName);
        g_CatCache[i].recLength = readIntFromByteArray(byteArray, 20);
        g_CatCache[i].recsPerPg = readIntFromByteArray(byteArray, 24);
        g_CatCache[i].numAttrs = readIntFromByteArray(byteArray, 28);
        g_CatCache[i].numRecs = readIntFromByteArray(byteArray, 32);
        g_CatCache[i].numPgs = readIntFromByteArray(byteArray, 36);

        g_CatCache[i].relcatRid = *foundRid;
        g_CatCache[i].dirty = FALSE;

        g_CatCache[i].relFile = open(relName, O_RDWR);

        startRid.pid = 1;
        startRid.slotnum = 0;

        returnVal = FindRec(ATTRCAT_CACHE, &startRid, &foundRid, &byteArray, 's', RELNAME, 32,
                relName, EQ);

        if (returnVal == NOTOK) {
            return ErrorMsgs(NO_ATTRS_FOUND, g_PrintFlag);
        }

        while (returnVal == OK) {
            newNode = malloc(sizeof(struct attrCatalog));

            if (isFirstExecution == TRUE) {
                g_CatCache[i].attrList = newNode;
                temp = newNode;
                isFirstExecution = FALSE;
            } else {
                temp->next = newNode;
                temp = newNode;
            }

            temp->offset = readIntFromByteArray(byteArray, 0);
            temp->length = readIntFromByteArray(byteArray, 4);
            temp->type = readIntFromByteArray(byteArray, 8);
            readStringFromByteArray(temp->attrName, byteArray, 12, RELNAME);
            readStringFromByteArray(temp->relName, byteArray, 32, RELNAME);
            temp->next = NULL;

            startRid = *foundRid;
            free(foundRid);
            returnVal = FindRec(ATTRCAT_CACHE, &startRid, &foundRid, &byteArray, 's', RELNAME, 32,
                    relName, EQ);
        }
        return i;
    }
}
